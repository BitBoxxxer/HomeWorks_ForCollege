USE TechStore_DWH;
GO

-- 1
IF NOT EXISTS (SELECT 1 FROM sys.schemas WHERE name = N'mart')
    EXEC (N'CREATE SCHEMA mart');
GO

-- 2
CREATE OR ALTER VIEW mart.vw_SalesByMonthCategory
AS
SELECT
    d.[Year]                                   AS [Year],
    d.[Month]                                  AS MonthNumber,
    d.MonthName                                AS MonthName,
    p.Category                                 AS Category,
    COUNT(DISTINCT f.OrderID)                  AS OrdersCount,
    SUM(f.Quantity)                            AS UnitsSold,
    CAST(SUM(f.Amount) AS DECIMAL(18,2))       AS Revenue,
    CAST(SUM(f.Amount) / NULLIF(COUNT(DISTINCT f.OrderID), 0) AS DECIMAL(18,2)) AS AvgRevenuePerOrder
FROM dbo.FactSales   AS f
JOIN dbo.DimDate     AS d ON d.DateKey    = f.DateKey
JOIN dbo.DimProduct  AS p ON p.ProductKey = f.ProductKey
GROUP BY d.[Year], d.[Month], d.MonthName, p.Category;
GO

-- 3
CREATE OR ALTER VIEW mart.vw_ProductPerformance
AS
SELECT
    p.ProductID                                AS ProductID,
    p.ProductName                              AS ProductName,
    p.Category                                 AS Category,
    COUNT(DISTINCT f.OrderID)                  AS OrdersCount,
    COALESCE(SUM(f.Quantity), 0)               AS UnitsSold,
    CAST(COALESCE(SUM(f.Amount), 0) AS DECIMAL(18,2)) AS Revenue,
    CAST(SUM(f.Amount) / NULLIF(SUM(f.Quantity), 0) AS DECIMAL(18,2)) AS AvgHistoricalUnitPrice
FROM dbo.DimProduct AS p
LEFT JOIN dbo.FactSales AS f ON f.ProductKey = p.ProductKey
GROUP BY p.ProductKey, p.ProductID, p.ProductName, p.Category;
GO

--4 
CREATE OR ALTER VIEW mart.vw_CustomerValue
AS
SELECT
    c.CustomerID                               AS CustomerID,
    c.FirstName                                AS FirstName,
    c.LastName                                 AS LastName,
    c.City                                     AS City,
    COUNT(DISTINCT f.OrderID)                  AS OrdersCount,
    COALESCE(SUM(f.Quantity), 0)               AS UnitsPurchased,
    CAST(COALESCE(SUM(f.Amount), 0) AS DECIMAL(18,2)) AS TotalSpent,
    CAST(SUM(f.Amount) / NULLIF(COUNT(DISTINCT f.OrderID), 0) AS DECIMAL(18,2)) AS AvgOrderValue
FROM dbo.DimCustomer AS c
LEFT JOIN dbo.FactSales AS f ON f.CustomerKey = c.CustomerKey
GROUP BY c.CustomerKey, c.CustomerID, c.FirstName, c.LastName, c.City;
GO

-- 5
CREATE OR ALTER VIEW mart.vw_SalesByCity
AS
SELECT
    c.City                                     AS City,
    COUNT(DISTINCT c.CustomerKey)              AS CustomersCount,
    COUNT(DISTINCT f.OrderID)                  AS OrdersCount,
    COALESCE(SUM(f.Quantity), 0)               AS UnitsSold,
    CAST(COALESCE(SUM(f.Amount), 0) AS DECIMAL(18,2)) AS Revenue,
    CAST(SUM(f.Amount) / NULLIF(COUNT(DISTINCT f.OrderID), 0) AS DECIMAL(18,2)) AS AvgOrderValue
FROM dbo.DimCustomer AS c
LEFT JOIN dbo.FactSales AS f ON f.CustomerKey = c.CustomerKey
GROUP BY c.City;
GO

--6
-- 6.1. Четыре обязательных VIEW схемы mart
SELECT
    s.name AS SchemaName,
    v.name AS ViewName
FROM sys.views   AS v
JOIN sys.schemas AS s ON s.schema_id = v.schema_id
WHERE s.name = N'mart'
  AND v.name IN (N'vw_SalesByMonthCategory', N'vw_ProductPerformance',
                 N'vw_CustomerValue',        N'vw_SalesByCity')
ORDER BY v.name;
GO

-- 6.2. Столбцы и типы mart.vw_SalesByMonthCategory
SELECT
    c.column_id AS ColumnId,
    c.name      AS ColumnName,
    t.name      AS DataType,
    c.max_length AS MaxLength,
    c.precision AS [Precision],
    c.scale     AS Scale
FROM sys.columns AS c
JOIN sys.types   AS t ON t.user_type_id = c.user_type_id
WHERE c.object_id = OBJECT_ID(N'mart.vw_SalesByMonthCategory')
ORDER BY c.column_id;
GO

-- 7
-- 4.1
SELECT TOP (5)
    ProductName, Category, OrdersCount, UnitsSold, Revenue
FROM mart.vw_ProductPerformance
ORDER BY Revenue DESC, ProductName;
GO

-- 4.2
SELECT TOP (3)
    FirstName, LastName, City, OrdersCount, UnitsPurchased, TotalSpent
FROM mart.vw_CustomerValue
ORDER BY TotalSpent DESC, LastName, FirstName;
GO

-- 4.3
SELECT TOP (1)
    City, CustomersCount, OrdersCount, UnitsSold, Revenue
FROM mart.vw_SalesByCity
ORDER BY Revenue DESC, City;
GO

-- 4.4
SELECT TOP (1)
    [Year], MonthNumber, MonthName, Category, OrdersCount, UnitsSold, Revenue
FROM mart.vw_SalesByMonthCategory
ORDER BY Revenue DESC, [Year], MonthNumber, Category;
GO

/* ---------------------------------------------------------------
   Шаг 8. Итоговые проверки
   После запуска этого файла выполнить sql/90_final_checks_lab03.sql
   и снять 4 контрольных скриншота.
   --------------------------------------------------------------- */
