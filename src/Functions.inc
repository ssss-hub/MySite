<?php

function setDB($dbName) {
    // $dsn      = 'mysql:dbname=' . $dbName . ';host=localhost';
    $dsn      = 'mysql:dbname=' . $dbName . ';host=db';
    $user     = 'root';
    $password = 'root';
    try {
        $dbh = new PDO($dsn, $user, $password);
    } catch(PDOException $e) {
        print("データベースの接続に失敗しました".$e->getMessage());
        die();
    }
    return $dbh;
}

function selectData($dbName, $sql, $bindList = NULL) {
    $dbh   = setDB($dbName);
    $stmt = $dbh->prepare($sql);
    if ($bindList != NULL) {
        foreach ($bindList as $key => $value) {
            $stmt->bindValue($key, $value);
        }
    }
    $stmt->execute();

    $dbh = null;
    return $stmt->fetchAll(PDO::FETCH_ASSOC);
}

function operateData($dbName, $sql, $bindList = NULL) {
    $dbh = setDB($dbName);

    try {
        $stmt = $dbh->prepare($sql);
        $stmt->execute($bindList);
    } catch(PDOException $e) {
        echo $e->getMessage();
        die();
    }
    $dbh = null;
}
?>