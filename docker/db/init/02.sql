CREATE DATABASE IF NOT EXISTS ssbu_db;

CREATE TABLE IF NOT EXISTS ssbu_db.CharacterTable(
    CharacterId INT(10) NOT NULL,
    CharacterSubId INT(10) NOT NULL,
    CharacterName NVARCHAR(100) NOT NULL,
    CharacterNameHiragana NVARCHAR(100),
    CharacterWeight DOUBLE,
    CharacterMovingSpeed DOUBLE,
    CharacterSwoopSpeed DOUBLE,
    CharacterFallSpeed DOUBLE,
    PRIMARY KEY(CharacterId, CharactersubId)
);

CREATE TABLE IF NOT EXISTS ssbu_db.CharacterMemoTable(
    CharacterId INT(10) NOT NULL,
    CharacterSubId INT(10) NOT NULL,
    CharacterMemo TEXT,
    PRIMARY KEY(CharacterId, CharactersubId)
);