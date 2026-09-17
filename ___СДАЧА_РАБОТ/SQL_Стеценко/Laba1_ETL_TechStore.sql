-- OLTP: TechStor
IF DB_ID('TechStore') IS NULL
    CREATE DATABASE TechStore;
GO

USE TechStore;
GO

IF OBJECT_ID('dbo.OrderItems') IS NOT NULL DROP TABLE dbo.OrderItems;
IF OBJECT_ID('dbo.Orders')     IS NOT NULL DROP TABLE dbo.Orders;
IF OBJECT_ID('dbo.Products')   IS NOT NULL DROP TABLE dbo.Products;
IF OBJECT_ID('dbo.Customers')  IS NOT NULL DROP TABLE dbo.Customers;
GO

CREATE TABLE dbo.Customers (
    CustomerID  INT IDENTITY(1,1) PRIMARY KEY,
    FirstName   NVARCHAR(50)  NOT NULL,
    LastName    NVARCHAR(50)  NOT NULL,
    Email       NVARCHAR(100) NULL,
    City        NVARCHAR(100) NOT NULL
);
GO

CREATE TABLE dbo.Products (
    ProductID   INT IDENTITY(1,1) PRIMARY KEY,
    ProductName NVARCHAR(100)  NOT NULL,
    Category    NVARCHAR(100)  NOT NULL,
    Price       DECIMAL(12,2)  NOT NULL CHECK (Price >= 0)
);
GO

CREATE TABLE dbo.Orders (
    OrderID     INT IDENTITY(1,1) PRIMARY KEY,
    CustomerID  INT NOT NULL FOREIGN KEY REFERENCES dbo.Customers(CustomerID),
    OrderDate   DATE NOT NULL
);
GO

CREATE TABLE dbo.OrderItems (
    OrderItemID INT IDENTITY(1,1) PRIMARY KEY,
    OrderID     INT NOT NULL FOREIGN KEY REFERENCES dbo.Orders(OrderID),
    ProductID   INT NOT NULL FOREIGN KEY REFERENCES dbo.Products(ProductID),
    Quantity    INT NOT NULL CHECK (Quantity > 0),
    Price       DECIMAL(12,2) NOT NULL CHECK (Price >= 0)  -- историческая цена продажи
);
GO

-- DWH: TechStore_DWH
IF DB_ID('TechStore_DWH') IS NULL
    CREATE DATABASE TechStore_DWH;
GO

USE TechStore_DWH;
GO

IF OBJECT_ID('dbo.FactSales')   IS NOT NULL DROP TABLE dbo.FactSales;
IF OBJECT_ID('dbo.DimDate')     IS NOT NULL DROP TABLE dbo.DimDate;
IF OBJECT_ID('dbo.DimProduct')  IS NOT NULL DROP TABLE dbo.DimProduct;
IF OBJECT_ID('dbo.DimCustomer') IS NOT NULL DROP TABLE dbo.DimCustomer;
GO

CREATE TABLE dbo.DimCustomer (
    CustomerKey INT IDENTITY(1,1) PRIMARY KEY,
    CustomerID  INT NOT NULL UNIQUE,
    FirstName   NVARCHAR(50)  NOT NULL,
    LastName    NVARCHAR(50)  NOT NULL,
    City        NVARCHAR(100) NOT NULL
);
GO

CREATE TABLE dbo.DimProduct (
    ProductKey  INT IDENTITY(1,1) PRIMARY KEY,
    ProductID   INT NOT NULL UNIQUE,
    ProductName NVARCHAR(100) NOT NULL,
    Category    NVARCHAR(100) NOT NULL
);
GO

CREATE TABLE dbo.DimDate (
    DateKey     INT PRIMARY KEY,
    FullDate    DATE NOT NULL UNIQUE,
    [Day]       INT NOT NULL,
    [Month]     INT NOT NULL,
    MonthName   NVARCHAR(20) NOT NULL,
    Quarter     INT NOT NULL,
    [Year]      INT NOT NULL
);
GO

CREATE TABLE dbo.FactSales (
    SalesKey    INT IDENTITY(1,1) PRIMARY KEY,
    OrderID     INT NOT NULL,
    DateKey     INT NOT NULL FOREIGN KEY REFERENCES dbo.DimDate(DateKey),
    CustomerKey INT NOT NULL FOREIGN KEY REFERENCES dbo.DimCustomer(CustomerKey),
    ProductKey  INT NOT NULL FOREIGN KEY REFERENCES dbo.DimProduct(ProductKey),
    Quantity    INT NOT NULL,
    Price       DECIMAL(12,2) NOT NULL,
    Amount      DECIMAL(12,2) NOT NULL
);
GO

USE TechStore;
GO

SET IDENTITY_INSERT dbo.Customers ON;
INSERT INTO dbo.Customers (CustomerID, FirstName, LastName, Email, City) VALUES
(1,  N'Иван',     N'Иванов',    'ivan@example.com',    N'Москва'),
(2,  N'Пётр',     N'Петров',    'petr@example.com',    N'Санкт-Петербург'),
(3,  N'Анна',     N'Смирнова',  'anna@example.com',    N'Казань'),
(4,  N'Мария',    N'Кузнецова', 'maria@example.com',   N'Москва'),
(5,  N'Алексей',  N'Попов',     'alexey@example.com',  N'Екатеринбург'),
(6,  N'Елена',    N'Васильева', 'elena@example.com',   N'Новосибирск'),
(7,  N'Дмитрий',  N'Соколов',   'dmitry@example.com',  N'Москва'),
(8,  N'Ольга',    N'Морозова',  'olga@example.com',    N'Казань'),
(9,  N'Сергей',   N'Волков',    'sergey@example.com',  N'Екатеринбург'),
(10, N'Наталья',  N'Фёдорова',  'natalia@example.com', N'Санкт-Петербург');
SET IDENTITY_INSERT dbo.Customers OFF;
GO

SET IDENTITY_INSERT dbo.Products ON;
INSERT INTO dbo.Products (ProductID, ProductName, Category, Price) VALUES
(1,  N'Ноутбук Pro 14',           N'Ноутбуки',   120000),
(2,  N'Ноутбук Air 13',           N'Ноутбуки',    90000),
(3,  N'Монитор 27',               N'Мониторы',    35000),
(4,  N'Монитор 24',               N'Мониторы',    22000),
(5,  N'Клавиатура Механическая',  N'Периферия',    8000),
(6,  N'Мышь Gaming',              N'Периферия',    5000),
(7,  N'Наушники Pro',             N'Аудио',       15000),
(8,  N'Веб-камера HD',            N'Периферия',    7000),
(9,  N'SSD 1TB',                  N'Накопители',  10000),
(10, N'SSD 2TB',                  N'Накопители',  18000),
(11, N'HDD 2TB',                  N'Накопители',   9000),
(12, N'Планшет 10',               N'Планшеты',    30000),
(13, N'Смартфон Pro',             N'Смартфоны',   70000),
(14, N'Смартфон Lite',            N'Смартфоны',   40000),
(15, N'Док-станция USB-C',        N'Периферия',   12000);
SET IDENTITY_INSERT dbo.Products OFF;
GO

SET IDENTITY_INSERT dbo.Orders ON;
INSERT INTO dbo.Orders (OrderID, CustomerID, OrderDate) VALUES
(1001, 1,  '2026-01-10'),
(1002, 2,  '2026-01-15'),
(1003, 3,  '2026-01-20'),
(1004, 1,  '2026-02-05'),
(1005, 4,  '2026-02-12'),
(1006, 5,  '2026-02-20'),
(1007, 6,  '2026-03-03'),
(1008, 7,  '2026-03-10'),
(1009, 8,  '2026-03-15'),
(1010, 9,  '2026-03-25'),
(1011, 10, '2026-04-02'),
(1012, 2,  '2026-04-12'),
(1013, 3,  '2026-04-20'),
(1014, 4,  '2026-05-05'),
(1015, 5,  '2026-05-18'),
(1016, 1,  '2026-06-01'),
(1017, 6,  '2026-06-15'),
(1018, 7,  '2026-07-10'),
(1019, 8,  '2026-08-05'),
(1020, 10, '2026-09-01');
SET IDENTITY_INSERT dbo.Orders OFF;
GO

SET IDENTITY_INSERT dbo.OrderItems ON;
INSERT INTO dbo.OrderItems (OrderItemID, OrderID, ProductID, Quantity, Price) VALUES
(1,  1001, 1,  1, 120000),
(2,  1001, 5,  1, 8000),
(3,  1001, 6,  1, 5000),
(4,  1002, 2,  1, 90000),
(5,  1002, 7,  1, 15000),
(6,  1003, 3,  2, 35000),
(7,  1003, 5,  1, 8000),
(8,  1004, 13, 1, 70000),
(9,  1004, 9,  1, 10000),
(10, 1005, 4,  1, 22000),
(11, 1005, 8,  1, 7000),
(12, 1005, 6,  2, 5000),
(13, 1006, 12, 1, 30000),
(14, 1006, 10, 1, 18000),
(15, 1007, 1,  1, 120000),
(16, 1007, 7,  1, 15000),
(17, 1008, 2,  2, 90000),
(18, 1008, 6,  1, 5000),
(19, 1009, 13, 1, 70000),
(20, 1009, 14, 1, 40000),
(21, 1010, 3,  1, 35000),
(22, 1010, 4,  1, 22000),
(23, 1010, 5,  1, 8000),
(24, 1011, 11, 1, 9000),
(25, 1011, 9,  2, 10000),
(26, 1012, 1,  1, 120000),
(27, 1012, 15, 1, 12000),
(28, 1013, 12, 2, 30000),
(29, 1013, 8,  1, 7000),
(30, 1014, 13, 1, 70000),
(31, 1014, 7,  1, 15000),
(32, 1015, 2,  1, 90000),
(33, 1015, 10, 1, 18000),
(34, 1016, 1,  1, 120000),
(35, 1016, 3,  1, 35000),
(36, 1017, 14, 1, 40000),
(37, 1017, 6,  2, 5000),
(38, 1018, 2,  1, 90000),
(39, 1018, 5,  1, 8000),
(40, 1019, 13, 1, 70000),
(41, 1019, 9,  1, 10000),
(42, 1020, 1,  1, 120000),
(43, 1020, 15, 1, 12000);
SET IDENTITY_INSERT dbo.OrderItems OFF;
GO

SELECT 'Customers' AS TableName, COUNT(*) AS RowCount FROM dbo.Customers
UNION ALL SELECT 'Products', COUNT(*) FROM dbo.Products
UNION ALL SELECT 'Orders', COUNT(*) FROM dbo.Orders
UNION ALL SELECT 'OrderItems', COUNT(*) FROM dbo.OrderItems;

SELECT
    SUM(Quantity) AS TotalUnits,
    SUM(CAST(Quantity AS DECIMAL(18,2)) * Price) AS TotalRevenue
FROM dbo.OrderItems;
GO


USE TechStore_DWH;
GO

INSERT INTO dbo.DimCustomer (CustomerID, FirstName, LastName, City)
SELECT
    CustomerID,
    FirstName,
    LastName,
    City
FROM TechStore.dbo.Customers;
GO

SELECT COUNT(*) AS DimCustomer_Rows FROM dbo.DimCustomer;
GO

INSERT INTO dbo.DimProduct (ProductID, ProductName, Category)
SELECT
    ProductID,
    ProductName,
    Category
FROM TechStore.dbo.Products;
GO

SELECT COUNT(*) AS DimProduct_Rows FROM dbo.DimProduct;
GO

INSERT INTO dbo.DimDate (DateKey, FullDate, [Day], [Month], MonthName, Quarter, [Year])
SELECT
    CONVERT(INT, CONVERT(CHAR(8), OrderDate, 112))  AS DateKey,
    OrderDate                                        AS FullDate,
    DAY(OrderDate)                                   AS [Day],
    MONTH(OrderDate)                                 AS [Month],
    DATENAME(MONTH, OrderDate)                        AS MonthName,
    DATEPART(QUARTER, OrderDate)                      AS Quarter,
    YEAR(OrderDate)                                   AS [Year]
FROM (
    SELECT DISTINCT OrderDate
    FROM TechStore.dbo.Orders
) AS UniqueDates;
GO

SELECT COUNT(*) AS DimDate_Rows FROM dbo.DimDate;
GO

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


SELECT 'DimCustomer' AS TableName, COUNT(*) AS RowCount FROM dbo.DimCustomer
UNION ALL SELECT 'DimProduct', COUNT(*) FROM dbo.DimProduct
UNION ALL SELECT 'DimDate', COUNT(*) FROM dbo.DimDate
UNION ALL SELECT 'FactSales', COUNT(*) FROM dbo.FactSales;

SELECT
    SUM(Quantity)  AS TotalUnits,
    SUM(Amount)    AS TotalRevenue
FROM dbo.FactSales;
GO


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