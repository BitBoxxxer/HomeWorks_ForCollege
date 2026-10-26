USE TechStore;
GO

SET XACT_ABORT ON;

BEGIN TRY
    BEGIN TRANSACTION;
    IF (SELECT SUM(BadRows) FROM stg.vValidationSummary) > 0
        THROW 50001, N'Validation нашла некорректные строки. Load отменён.', 1;
    SET IDENTITY_INSERT dbo.Customers ON;

    INSERT INTO dbo.Customers (CustomerID, FirstName, LastName, Email, City)
    SELECT s.CustomerID, s.FirstName, s.LastName, s.Email, s.City
    FROM stg.vCustomersClean AS s
    WHERE NOT EXISTS (SELECT 1 FROM dbo.Customers AS d WHERE d.CustomerID = s.CustomerID);

    SET IDENTITY_INSERT dbo.Customers OFF;
    SET IDENTITY_INSERT dbo.Products ON;

    INSERT INTO dbo.Products (ProductID, ProductName, Category, Price)
    SELECT s.ProductID, s.ProductName, s.Category, s.Price
    FROM stg.vProductsClean AS s
    WHERE NOT EXISTS (SELECT 1 FROM dbo.Products AS d WHERE d.ProductID = s.ProductID);

    SET IDENTITY_INSERT dbo.Products OFF;
    SET IDENTITY_INSERT dbo.Orders ON;

    INSERT INTO dbo.Orders (OrderID, CustomerID, OrderDate)
    SELECT s.OrderID, s.CustomerID, s.OrderDate
    FROM stg.vOrdersClean AS s
    WHERE NOT EXISTS (SELECT 1 FROM dbo.Orders AS d WHERE d.OrderID = s.OrderID);

    SET IDENTITY_INSERT dbo.Orders OFF;

    SET IDENTITY_INSERT dbo.OrderItems ON;

    INSERT INTO dbo.OrderItems (OrderItemID, OrderID, ProductID, Quantity, Price)
    SELECT s.OrderItemID, s.OrderID, s.ProductID, s.Quantity, s.Price
    FROM stg.vOrderItemsClean AS s
    WHERE NOT EXISTS (SELECT 1 FROM dbo.OrderItems AS d WHERE d.OrderItemID = s.OrderItemID);

    SET IDENTITY_INSERT dbo.OrderItems OFF;

    COMMIT TRANSACTION;
    PRINT N'Load выполнен успешно.';
END TRY
BEGIN CATCH
    IF @@TRANCOUNT > 0
        ROLLBACK TRANSACTION;

    SET IDENTITY_INSERT dbo.Customers  OFF;
    SET IDENTITY_INSERT dbo.Products   OFF;
    SET IDENTITY_INSERT dbo.Orders     OFF;
    SET IDENTITY_INSERT dbo.OrderItems OFF;

    THROW;
END CATCH;
GO

-- OLTP
SELECT 'Customers' AS TableName, COUNT(*) AS [RowCount] FROM dbo.Customers
UNION ALL SELECT 'Products',   COUNT(*) FROM dbo.Products
UNION ALL SELECT 'Orders',     COUNT(*) FROM dbo.Orders
UNION ALL SELECT 'OrderItems', COUNT(*) FROM dbo.OrderItems;
SELECT
    SUM(Quantity) AS TotalUnits,
    SUM(CAST(Quantity AS DECIMAL(18,2)) * Price) AS TotalRevenue
FROM dbo.OrderItems;
GO
SELECT
    COUNT(*)      AS ImportedItems,
    SUM(Quantity) AS ImportedUnits,
    SUM(CAST(Quantity AS DECIMAL(18,2)) * Price) AS ImportedRevenue
FROM dbo.OrderItems
WHERE OrderID BETWEEN 1021 AND 1025;
GO
