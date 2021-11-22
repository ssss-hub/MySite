<?php require_once("./chara_detail.inc"); ?>
<!doctype html>
<html lang="ja">
<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <!-- <script type="text/javascript" src="./js/marked.js"></script> -->
    <!-- <script src="https://cdn.rawgit.com/chjj/marked/master/marked.min.js"></script> -->
    <!-- <script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script> -->

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../../common.css">
    <title>詳細画面</title>
</head>

<body>
    <div class="container">
        <h1>キャラ対策</h1>
        <?php foreach ($data as $character) { ?>
            <h2><?php echo $character['CharacterName']; ?></h2>
            <div>
                <?php echo $character['CharacterMemo']; ?>
            </div>
        <?php } ?>
        <br>
        <input type="button" onclick="location.href='./chara_search.php'" value="戻る" class="btn btn-primary">
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    
</body>

</html>