CREATE DATABASE IF NOT EXISTS recipe_db;

CREATE TABLE IF NOT EXISTS recipe_db.MaterialTable(
  RecipeId INT(10) NOT NULL,
  MaterialId INT(10) NOT NULL,
  MaterialName NVARCHAR(200) NOT NULL,
  MaterialNameHiragana NVARCHAR(200) NOT NULL,
  Quantity DOUBLE,
  Unit NVARCHAR(200) NOT NULL,
  PRIMARY KEY(RecipeId, MaterialId)
);

CREATE TABLE IF NOT EXISTS recipe_db.PointTable(
  RecipeId INT(10) NOT NULL,
  PointId INT(10) NOT NULL,
  PointContent NVARCHAR(1000) NOT NULL,
  PRIMARY KEY(RecipeId, PointId)
);

CREATE TABLE IF NOT EXISTS recipe_db.ProcessTable(
  RecipeId INT(10) NOT NULL,
  ProcessId INT(10) NOT NULL,
  ProcessContent NVARCHAR(1000) NOT NULL,
  ProcessPhotoUrl NVARCHAR(3000),
  PRIMARY KEY(RecipeId, ProcessId)
);

CREATE TABLE IF NOT EXISTS recipe_db.RecipeTable(
  RecipeId INT(10) PRIMARY KEY NOT NULL,
  RecipeName NVARCHAR(1000) NOT NULL,
  RecipeNameHiragana NVARCHAR(1000) NOT NULL,
  CompletedPhotoUrl NVARCHAR(3000),
  ReferenceUrl NVARCHAR(3000)
);