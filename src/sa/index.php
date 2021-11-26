<?php require_once("./index.inc"); ?>
<!doctype html>
<html lang="ja">

<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../common.css">
    <title>開発中</title>
</head>

<body>
    <div class="container">
        <h1>開発中</h1>
        <h2>登録</h2>
        <li><a href="register.php">登録</a></li>
        <h2>吟味(残サイト:<?php echo number_format($data['SELECT_SITE_COUNT']); ?>つ、残URL:<?php echo number_format($data['SELECT_URL_COUNT']); ?>枚)</h2>
        <li><a href="select.php?newOnly=1&sort=count_asc">枚数少ない順</a></li>
        <li><a href="select.php?newOnly=1&sort=count_desc">枚数多い順</a></li>
        <li><a href="select.php?newOnly=1&sort=page_id_asc">登録古い順</a></li>
        <li><a href="select.php?newOnly=1&sort=page_id_desc">登録新しい順</a></li>
        <li><a href="select.php?newOnly=1&sort=page_title_asc">ページタイトル昇順</a></li>
        <li><a href="select.php?newOnly=1&sort=page_title_desc">ページタイトル降順</a></li>
        <h2>全体</h2>
        <li><a href="select_detail.php?multiple=true">かぶり</a></li>
        <li><a href="select_detail.php?big_size=true&photo=true">サイズ大きい順photo</a></li>
        <li><a href="select_detail.php?big_size=true&gif=true">サイズ大きい順gif</a></li>
        <h2>データ検索</h2>
        <li><a href="check_data.php?pattern=1">ページのnewだけ</a></li>
        <li><a href="check_data.php?pattern=2">ページの全部</a></li>
        <li><a href="check_data.php?pattern=3">UrlのNewだけ</a></li>
        <li><a href="check_data.php?pattern=4">UrlのUpdateDateが空、garbage</a></li>
        <h2>通過(枚数:<?php echo number_format($data['OK_COUNT']); ?>件)</h2>
        <li><a href="select_detail.php?okOnly=1&sort=update_asc">登録古い順</a></li>
        <li><a href="select_detail.php?okOnly=1&sort=update_desc">登録新しい順</a></li>
        <li><a href="select_detail.php?okOnly=1&sort=size_asc">サイズ小さい順</a></li>
        <li><a href="select_detail.php?okOnly=1&sort=size_desc">サイズ大きい順</a></li>
        <li><a href="select_detail.php?okOnly=1&sort=random">ランダム</a></li>
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>