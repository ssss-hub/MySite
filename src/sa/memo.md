# DB定義
## PageTable
| 属性名     | PK   | 型       | 桁数 | NotNull |
| ---------- | ---- | -------- | ---- | ------- |
| PageId     | ○    | INT      | 10   | ○       |
| PageUrl    |      | nvarchar | 1000 | ○       |
| PageTitle  |      | nvarchar | 1000 |         |
| PageStatus |      | nvarchar | 30   | ○       |
### SQL
```sql
DROP TABLE as_db.PageTable;
CREATE TABLE as_db.PageTable(
    PageId INT(10) PRIMARY KEY NOT NULL,
    PageUrl NVARCHAR(1000) NOT NULL,
    PageTitle NVARCHAR(1000),
    PageStatus NVARCHAR(30)
);
```
## UrlTable
| 属性名     | PK   | 型       | 桁数 | NotNull |
| ---------- | ---- | -------- | ---- | ------- |
| UrlId      | ○    | INT      | 10   | ○       |
| PageId     | ○    | INT      | 10   | ○       |
| Url        |      | nvarchar | 1000 | ○       |
| FileName   |      | nvarchar | 30   | ○       |
| FileStatus |      | nvarchar | 30   | ○       |
| FileSize   |      | INT      | 10   |         |
| FileHeight |      | INT      | 10   |         |
| FileWidth  |      | INT      | 10   |         |
| UpdateDate |      | Datetime |      |         |
### SQL
```sql
DROP TABLE as_db.UrlTable;
CREATE TABLE as_db.UrlTable(
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
```