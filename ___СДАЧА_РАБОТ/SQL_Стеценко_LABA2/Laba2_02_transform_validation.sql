USE TechStore;
GO

-- 1
CREATE VIEW stg.vCustomersClean AS
SELECT
    TRY_CONVERT(INT, c.CustomerID) AS CustomerID,
    c.FirstName,
    c.LastName,
    c.Email,
    c.City,
    r.FirstName AS RawFirstName,
    r.LastName  AS RawLastName
FROM stg.CustomersImportRaw AS r
CROSS APPLY (
    SELECT
        NULLIF(TRIM(REPLACE(REPLACE(r.CustomerID, NCHAR(13), N''), NCHAR(160), N' ')), N'') AS CustomerID,
        NULLIF(TRIM(REPLACE(REPLACE(r.FirstName,  NCHAR(13), N''), NCHAR(160), N' ')), N'') AS FirstName,
        NULLIF(TRIM(REPLACE(REPLACE(r.LastName,   NCHAR(13), N''), NCHAR(160), N' ')), N'') AS LastName,
        NULLIF(TRIM(REPLACE(REPLACE(r.Email,      NCHAR(13), N''), NCHAR(160), N' ')), N'') AS Email,
        NULLIF(TRIM(REPLACE(REPLACE(r.City,       NCHAR(13), N''), NCHAR(160), N' ')), N'') AS City
) AS c;
GO

CREATE VIEW stg.vProductsClean AS
SELECT
    TRY_CONVERT(INT, c.ProductID) AS ProductID,
    c.ProductName,
    c.Category,
    TRY_CONVERT(DECIMAL(12,2), c.Price) AS Price,
    r.Price AS RawPrice
FROM stg.ProductsImportRaw AS r
CROSS APPLY (
    SELECT
        NULLIF(TRIM(REPLACE(REPLACE(r.ProductID,   NCHAR(13), N''), NCHAR(160), N' ')), N'') AS ProductID,
        NULLIF(TRIM(REPLACE(REPLACE(r.ProductName, NCHAR(13), N''), NCHAR(160), N' ')), N'') AS ProductName,
        NULLIF(TRIM(REPLACE(REPLACE(r.Category,    NCHAR(13), N''), NCHAR(160), N' ')), N'') AS Category,
        NULLIF(
            REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(
                r.Price COLLATE Cyrillic_General_BIN,
                NCHAR(8381), N''),
                NCHAR(13),   N''),
                NCHAR(160),  N''),
                NCHAR(8239), N''),
                N' ',        N''),
                N',',        N'.'),
            N'') AS Price
) AS c;
GO

-- Дата
CREATE VIEW stg.vOrdersClean AS
SELECT
    TRY_CONVERT(INT,  c.OrderID)    AS OrderID,
    TRY_CONVERT(INT,  c.CustomerID) AS CustomerID,
    TRY_CONVERT(DATE, c.OrderDate, 104) AS OrderDate,
    r.OrderDate AS RawOrderDate
FROM stg.OrdersImportRaw AS r
CROSS APPLY (
    SELECT
        NULLIF(TRIM(REPLACE(REPLACE(r.OrderID,    NCHAR(13), N''), NCHAR(160), N' ')), N'') AS OrderID,
        NULLIF(TRIM(REPLACE(REPLACE(r.CustomerID, NCHAR(13), N''), NCHAR(160), N' ')), N'') AS CustomerID,
        NULLIF(TRIM(REPLACE(REPLACE(r.OrderDate,  NCHAR(13), N''), NCHAR(160), N' ')), N'') AS OrderDate
) AS c;
GO

CREATE VIEW stg.vOrderItemsClean AS
SELECT
    TRY_CONVERT(INT, c.OrderItemID) AS OrderItemID,
    TRY_CONVERT(INT, c.OrderID)     AS OrderID,
    TRY_CONVERT(INT, c.ProductID)   AS ProductID,
    TRY_CONVERT(INT, c.Quantity)    AS Quantity,
    TRY_CONVERT(DECIMAL(12,2), c.Price) AS Price,
    r.Price AS RawPrice
FROM stg.OrderItemsImportRaw AS r
CROSS APPLY (
    SELECT
        NULLIF(TRIM(REPLACE(REPLACE(r.OrderItemID, NCHAR(13), N''), NCHAR(160), N' ')), N'') AS OrderItemID,
        NULLIF(TRIM(REPLACE(REPLACE(r.OrderID,     NCHAR(13), N''), NCHAR(160), N' ')), N'') AS OrderID,
        NULLIF(TRIM(REPLACE(REPLACE(r.ProductID,   NCHAR(13), N''), NCHAR(160), N' ')), N'') AS ProductID,
        NULLIF(TRIM(REPLACE(REPLACE(r.Quantity,    NCHAR(13), N''), NCHAR(160), N' ')), N'') AS Quantity,
        NULLIF(
            REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(
                r.Price COLLATE Cyrillic_General_BIN,
                NCHAR(8381), N''),
                NCHAR(13),   N''),
                NCHAR(160),  N''),
                NCHAR(8239), N''),
                N' ',        N''),
                N',',        N'.'),
            N'') AS Price
) AS c;
GO

-- 2 PREVIEW
SELECT CustomerID, RawFirstName, FirstName, RawLastName, LastName, Email, City
FROM stg.vCustomersClean;

-- Products
SELECT ProductID, ProductName, Category, RawPrice, Price
FROM stg.vProductsClean;

SELECT OrderID, CustomerID, RawOrderDate, OrderDate
FROM stg.vOrdersClean;

SELECT OrderItemID, OrderID, ProductID, Quantity, RawPrice, Price
FROM stg.vOrderItemsClean;
GO

-- 3. VALIDATION
CREATE VIEW stg.vValidationSummary AS
SELECT 'Customers' AS TableName, COUNT(*) AS BadRows
FROM stg.vCustomersClean
WHERE CustomerID IS NULL OR FirstName IS NULL OR LastName IS NULL OR City IS NULL

UNION ALL
SELECT 'Products', COUNT(*)
FROM stg.vProductsClean
WHERE ProductID IS NULL OR ProductName IS NULL OR Category IS NULL
   OR Price IS NULL OR Price < 0

UNION ALL
SELECT 'Orders', COUNT(*)
FROM stg.vOrdersClean AS o
WHERE o.OrderID IS NULL OR o.CustomerID IS NULL OR o.OrderDate IS NULL
   OR (o.CustomerID IS NOT NULL
       AND NOT EXISTS (SELECT 1 FROM dbo.Customers AS d WHERE d.CustomerID = o.CustomerID)
       AND NOT EXISTS (SELECT 1 FROM stg.vCustomersClean AS s WHERE s.CustomerID = o.CustomerID))

UNION ALL
SELECT 'OrderItems', COUNT(*)
FROM stg.vOrderItemsClean AS i
WHERE i.OrderItemID IS NULL OR i.OrderID IS NULL OR i.ProductID IS NULL
   OR i.Quantity IS NULL OR i.Quantity <= 0
   OR i.Price IS NULL OR i.Price < 0
   OR (i.OrderID IS NOT NULL
       AND NOT EXISTS (SELECT 1 FROM dbo.Orders AS d WHERE d.OrderID = i.OrderID)
       AND NOT EXISTS (SELECT 1 FROM stg.vOrdersClean AS s WHERE s.OrderID = i.OrderID))
   OR (i.ProductID IS NOT NULL
       AND NOT EXISTS (SELECT 1 FROM dbo.Products AS d WHERE d.ProductID = i.ProductID)
       AND NOT EXISTS (SELECT 1 FROM stg.vProductsClean AS s WHERE s.ProductID = i.ProductID))

UNION ALL
SELECT 'Duplicate IDs in files', COUNT(*) FROM (
    SELECT CustomerID  FROM stg.vCustomersClean   GROUP BY CustomerID  HAVING COUNT(*) > 1
    UNION ALL
    SELECT ProductID   FROM stg.vProductsClean    GROUP BY ProductID   HAVING COUNT(*) > 1
    UNION ALL
    SELECT OrderID     FROM stg.vOrdersClean      GROUP BY OrderID     HAVING COUNT(*) > 1
    UNION ALL
    SELECT OrderItemID FROM stg.vOrderItemsClean  GROUP BY OrderItemID HAVING COUNT(*) > 1
) AS d;
GO

SELECT TableName, BadRows FROM stg.vValidationSummary;

SELECT SUM(BadRows) AS TotalBadRows FROM stg.vValidationSummary;
GO

SELECT * FROM stg.vCustomersClean
WHERE CustomerID IS NULL OR FirstName IS NULL OR LastName IS NULL OR City IS NULL;

SELECT * FROM stg.vProductsClean
WHERE ProductID IS NULL OR ProductName IS NULL OR Category IS NULL OR Price IS NULL OR Price < 0;

SELECT * FROM stg.vOrdersClean
WHERE OrderID IS NULL OR CustomerID IS NULL OR OrderDate IS NULL;

SELECT * FROM stg.vOrderItemsClean
WHERE OrderItemID IS NULL OR OrderID IS NULL OR ProductID IS NULL
   OR Quantity IS NULL OR Quantity <= 0 OR Price IS NULL OR Price < 0;
GO

-- Доп
SELECT
    (SELECT COUNT(*) FROM stg.vCustomersClean  s JOIN dbo.Customers  d ON d.CustomerID  = s.CustomerID)  AS ExistingCustomers,
    (SELECT COUNT(*) FROM stg.vProductsClean   s JOIN dbo.Products   d ON d.ProductID   = s.ProductID)   AS ExistingProducts,
    (SELECT COUNT(*) FROM stg.vOrdersClean     s JOIN dbo.Orders     d ON d.OrderID     = s.OrderID)     AS ExistingOrders,
    (SELECT COUNT(*) FROM stg.vOrderItemsClean s JOIN dbo.OrderItems d ON d.OrderItemID = s.OrderItemID) AS ExistingOrderItems;
GO
