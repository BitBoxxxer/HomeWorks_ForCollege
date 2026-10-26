USE TechStore_DWH;
GO

-- Очистка
DELETE FROM dbo.FactSales;
DELETE FROM dbo.DimDate;
DELETE FROM dbo.DimProduct;
DELETE FROM dbo.DimCustomer;

DBCC CHECKIDENT ('dbo.FactSales',   RESEED, 0);
DBCC CHECKIDENT ('dbo.DimProduct',  RESEED, 0);
DBCC CHECKIDENT ('dbo.DimCustomer', RESEED, 0);
GO

-- ETL из ЛР1
INSERT INTO dbo.DimCustomer (CustomerID, FirstName, LastName, City)
SELECT CustomerID, FirstName, LastName, City
FROM TechStore.dbo.Customers;
GO

INSERT INTO dbo.DimProduct (ProductID, ProductName, Category)
SELECT ProductID, ProductName, Category
FROM TechStore.dbo.Products;
GO

INSERT INTO dbo.DimDate (DateKey, FullDate, [Day], [Month], MonthName, Quarter, [Year])
SELECT
    CONVERT(INT, CONVERT(CHAR(8), OrderDate, 112)) AS DateKey,
    OrderDate                                      AS FullDate,
    DAY(OrderDate)                                 AS [Day],
    MONTH(OrderDate)                               AS [Month],
    DATENAME(MONTH, OrderDate)                     AS MonthName,
    DATEPART(QUARTER, OrderDate)                   AS Quarter,
    YEAR(OrderDate)                                AS [Year]
FROM (
    SELECT DISTINCT OrderDate
    FROM TechStore.dbo.Orders
) AS UniqueDates;
GO

INSERT INTO dbo.FactSales (OrderID, DateKey, CustomerKey, ProductKey, Quantity, Price, Amount)
SELECT
    o.OrderID,
    dd.DateKey,
    dc.CustomerKey,
    dp.ProductKey,
    oi.Quantity,
    oi.Price,
    CAST(oi.Quantity AS DECIMAL(12,2)) * oi.Price AS Amount
FROM TechStore.dbo.OrderItems AS oi
JOIN TechStore.dbo.Orders AS o
    ON o.OrderID = oi.OrderID
JOIN dbo.DimCustomer AS dc
    ON dc.CustomerID = o.CustomerID
JOIN dbo.DimProduct AS dp
    ON dp.ProductID = oi.ProductID
JOIN dbo.DimDate AS dd
    ON dd.FullDate = o.OrderDate;
GO

-- Проверка 2
SELECT 'DimCustomer' AS TableName, COUNT(*) AS [RowCount] FROM dbo.DimCustomer
UNION ALL SELECT 'DimProduct', COUNT(*) FROM dbo.DimProduct
UNION ALL SELECT 'DimDate',    COUNT(*) FROM dbo.DimDate
UNION ALL SELECT 'FactSales',  COUNT(*) FROM dbo.FactSales;
SELECT
    SUM(Quantity) AS TotalUnits,
    SUM(Amount)   AS TotalRevenue
FROM dbo.FactSales;
GO

-- DWH
SELECT
    dp.ProductName,
    SUM(fs.Quantity) AS UnitsSold,
    SUM(fs.Amount)   AS Revenue
FROM dbo.FactSales AS fs
JOIN dbo.DimProduct AS dp
    ON dp.ProductKey = fs.ProductKey
GROUP BY dp.ProductName
ORDER BY Revenue DESC;
GO
SELECT
    dp.Category,
    SUM(fs.Amount) AS Revenue
FROM dbo.FactSales AS fs
JOIN dbo.DimProduct AS dp
    ON dp.ProductKey = fs.ProductKey
GROUP BY dp.Category
ORDER BY Revenue DESC;
GO
SELECT
    dc.FirstName,
    dc.LastName,
    SUM(fs.Amount) AS TotalSpent
FROM dbo.FactSales AS fs
JOIN dbo.DimCustomer AS dc
    ON dc.CustomerKey = fs.CustomerKey
GROUP BY dc.FirstName, dc.LastName
ORDER BY TotalSpent DESC;
GO
SELECT TOP 1
    dc.FirstName,
    dc.LastName,
    SUM(fs.Amount) AS TotalSpent
FROM dbo.FactSales AS fs
JOIN dbo.DimCustomer AS dc
    ON dc.CustomerKey = fs.CustomerKey
GROUP BY dc.FirstName, dc.LastName
ORDER BY TotalSpent DESC;
GO

SELECT
    dd.[Year],
    dd.[Month],
    dd.MonthName,
    SUM(fs.Amount) AS Revenue
FROM dbo.FactSales AS fs
JOIN dbo.DimDate AS dd
    ON dd.DateKey = fs.DateKey
GROUP BY dd.[Year], dd.[Month], dd.MonthName
ORDER BY dd.[Year], dd.[Month];
GO

SELECT
    COUNT(*)        AS ImportedFactRows,
    SUM(Quantity)   AS ImportedUnits,
    SUM(Amount)     AS ImportedRevenue
FROM dbo.FactSales
WHERE OrderID BETWEEN 1021 AND 1025;
GO
