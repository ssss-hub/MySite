# SSB

## DB定義

### Database作成

#### SQL

```sql
CREATE DATABASE ssbu_db;
USE ssbu_db;
```

### CharacterTable

| 属性名                | PK   | 型       | 桁数 | NotNull |
| --------------------- | ---- | -------- | ---- | ------- |
| CharacterId           | ○    | INT      | 10   | ○       |
| CharacterSubId        | ○    | INT      | 10   | ○       |
| CharacterName         |      | nvarchar | 100  | ○       |
| CharacterNameHiragana |      | nvarchar | 1000 |         |
| CharacterWeight       |      | DOUBLE   |      |         |
| CharacterMovingSpeed  |      | DOUBLE   |      |         |
| CharacterSwoopSpeed   |      | DOUBLE   |      |         |
| CharacterFallSpeed    |      | DOUBLE   |      |         |


#### SQL

```sql
CREATE TABLE CharacterTable(
    CharacterId INT(10) NOT NULL,
    CharacterSubId INT(10) NOT NULL,
    CharacterName NVARCHAR(100) NOT NULL,
    CharacterNameHiragana NVARCHAR(100),
    CharacterWeight DOUBLE,
    CharacterMovingSpeed DOUBLE,
    CharacterSwoopSpeed DOUBLE,
    CharacterFallSpeed DOUBLE,
    PRIMARY KEY(CharacterId,CharactersubId));
);
```
### CharacterMemoTable

| 属性名                | PK   | 型       | 桁数 | NotNull |
| --------------------- | ---- | -------- | ---- | ------- |
| CharacterId           | ○    | INT      | 10   | ○       |
| CharacterSubId        | ○    | INT      | 10   | ○       |
| CharacterMemo         |      | TEXT     |      |         |


#### SQL

```sql
CREATE TABLE CharacterMemoTable(
    CharacterId INT(10) NOT NULL,
    CharacterSubId INT(10) NOT NULL,
    CharacterMemo TEXT,
    PRIMARY KEY(CharacterId,CharactersubId));
);
```