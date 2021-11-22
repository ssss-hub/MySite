<?php require_once("./chara_modify.inc"); ?>
<!doctype html>
<html lang="ja">
<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../../common.css">
    <title>編集画面</title>
</head>

<body>
    <div class="container">
        <h1>編集</h1>
        <h2><?php echo $data['CharacterName']; ?></h2>
        <form name="modify" action="chara_modify.php" method="POST">
            <textarea name="character_memo" cols="100" rows="30"><?php echo $data['CharacterMemo']; ?></textarea>
            <!-- <input type="text" name="character_memo" value="<?php //echo $data['CharacterMemo']; ?>"> -->
            <input type="hidden" name="character_id" value="<?php echo $data['CharacterId']; ?>">
            <input type="hidden" name="character_sub_id" value="<?php echo $data['CharacterSubId']; ?>">
            <br>
            <input type="submit" name="modify" value="編集" class="btn btn-success" />
            <input type="button" onclick="location.href='./chara_search.php'" value="戻る" class="btn btn-primary offset-1">
        </form>
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>