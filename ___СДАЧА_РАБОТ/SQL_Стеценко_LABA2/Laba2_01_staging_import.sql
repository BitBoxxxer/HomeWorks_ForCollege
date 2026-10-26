USE TechStore;
GO

-- 1
IF NOT EXISTS (SELECT 1 FROM sys.schemas WHERE name = 'stg')
    EXEC('CREATE SCHEMA stg');
GO
DROP VIEW  IF EXISTS stg.vValidationSummary;
DROP VIEW  IF EXISTS stg.vOrderItemsClean;
DROP VIEW  IF EXISTS stg.vOrdersClean;
DROP VIEW  IF EXISTS stg.vProductsClean;
DROP VIEW  IF EXISTS stg.vCustomersClean;
DROP TABLE IF EXISTS stg.OrderItemsImportRaw;
DROP TABLE IF EXISTS stg.OrdersImportRaw;
DROP TABLE IF EXISTS stg.ProductsImportRaw;
DROP TABLE IF EXISTS stg.CustomersImportRaw;
GO

-- 2 RAW
CREATE TABLE stg.CustomersImportRaw (
    CustomerID  NVARCHAR(50)  NULL,
    FirstName   NVARCHAR(200) NULL,
    LastName    NVARCHAR(200) NULL,
    Email       NVARCHAR(200) NULL,
    City        NVARCHAR(200) NULL
);

CREATE TABLE stg.ProductsImportRaw (
    ProductID   NVARCHAR(50)  NULL,
    ProductName NVARCHAR(200) NULL,
    Category    NVARCHAR(200) NULL,
    Price       NVARCHAR(100) NULL
);

CREATE TABLE stg.OrdersImportRaw (
    OrderID     NVARCHAR(50)  NULL,
    CustomerID  NVARCHAR(50)  NULL,
    OrderDate   NVARCHAR(50)  NULL
);

CREATE TABLE stg.OrderItemsImportRaw (
    OrderItemID NVARCHAR(50)  NULL,
    OrderID     NVARCHAR(50)  NULL,
    ProductID   NVARCHAR(50)  NULL,
    Quantity    NVARCHAR(50)  NULL,
    Price       NVARCHAR(100) NULL
);
GO

-- 3 BULK
BULK INSERT stg.CustomersImportRaw
FROM 'C:\TechStoreImport\01_Customers_import.csv'
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDQUOTE = '"',
    FIELDTERMINATOR = ';',
    ROWTERMINATOR = '0x0a',
    CODEPAGE = '65001'
);
GO

BULK INSERT stg.ProductsImportRaw
FROM 'C:\TechStoreImport\02_Products_import.csv'
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDQUOTE = '"',
    FIELDTERMINATOR = ';',
    ROWTERMINATOR = '0x0a',
    CODEPAGE = '65001'
);
GO

BULK INSERT stg.OrdersImportRaw
FROM 'C:\TechStoreImport\03_Orders_import.csv'
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDQUOTE = '"',
    FIELDTERMINATOR = ';',
    ROWTERMINATOR = '0x0a',
    CODEPAGE = '65001'
);
GO

BULK INSERT stg.OrderItemsImportRaw
FROM 'C:\TechStoreImport\04_OrderItems_import.csv'
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDQUOTE = '"',
    FIELDTERMINATOR = ';',
    ROWTERMINATOR = '0x0a',
    CODEPAGE = '65001'
);
GO

-- 4 RAW
SELECT 'CustomersImportRaw'  AS TableName, COUNT(*) AS [RowCount] FROM stg.CustomersImportRaw
UNION ALL SELECT 'ProductsImportRaw',   COUNT(*) FROM stg.ProductsImportRaw
UNION ALL SELECT 'OrdersImportRaw',     COUNT(*) FROM stg.OrdersImportRaw
UNION ALL SELECT 'OrderItemsImportRaw', COUNT(*) FROM stg.OrderItemsImportRaw;
GO
SELECT * FROM stg.CustomersImportRaw;
SELECT * FROM stg.ProductsImportRaw;
SELECT * FROM stg.OrdersImportRaw;
SELECT * FROM stg.OrderItemsImportRaw;
GO

-- 5
SELECT
    Price,
    UNICODE(RIGHT(Price, 1))                 AS LastCharCode_Price,
    UNICODE(RIGHT((SELECT TOP 1 OrderDate FROM stg.OrdersImportRaw), 1)) AS LastCharCode_OrderDate
FROM stg.ProductsImportRaw;
GO

-- 6
IF OBJECT_ID('stg.ProductsImportWizard') IS NOT NULL
    SELECT COLUMN_NAME, DATA_TYPE, CHARACTER_MAXIMUM_LENGTH
    FROM INFORMATION_SCHEMA.COLUMNS
    WHERE TABLE_SCHEMA = 'stg' AND TABLE_NAME = 'ProductsImportWizard'
    ORDER BY ORDINAL_POSITION;
GO
