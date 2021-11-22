CREATE DATABASE IF NOT EXISTS as_db;

CREATE TABLE IF NOT EXISTS as_db.PageTable(
    PageId INT(10) PRIMARY KEY NOT NULL,
    PageUrl NVARCHAR(1000) NOT NULL,
    PageTitle NVARCHAR(1000),
    PageStatus NVARCHAR(30)
);

CREATE TABLE IF NOT EXISTS as_db.UrlTable(
    UrlId INT(10) PRIMARY KEY NOT NULL,
    PageId INT(10) NOT NULL,
    Url NVARCHAR(1000) NOT NULL,
    FileName NVARCHAR(30),
    FileStatus NVARCHAR(30),
    FileSize INT(10),
    FileHeight INT(10),
    FileWidth INT(10),
    UpdateDate Datetime
);