<?php require_once("./chara_search.inc"); ?>
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
	<title>バースト択</title>
</head>

<body>
	<div class="container">
		<h1>キャラ検索</h1>
        <form name="search" action="chara_search.php" method="POST" class="form-horizontal">
            <div class="form-group">
                <label class="col-sm-2 control-label">検索ワード</label>
                <div class="col-sm-10">
                    <input type="text" name="searchWord" value="<?php echo @$_POST['searchWord']; ?>" class="form-control" />
                </div>
            </div>
			<input type="submit" value="検索" class="btn btn-success" />
			<input type="button" onclick="location.href='index.php'" value="戻る" class="btn btn-primary offset-1">
		</form>
        <br>
        <h2>一覧</h2>
        <table class="table table-striped table-bordered">
            <tr>
                <th>キャラ名</th>
                <th>詳細</th>
                <th>編集</th>
            </tr>
            <?php foreach ($data as $chara) { ?>
                <tr>
                    <td>
                        <?php echo $chara['CharacterName']; ?>
                    </td>
                    <td>
                        <?php if ($chara['IsDetail'] == '1') { ?>
                            <input type="button" onclick="location.href='./chara_detail.php?character_id=<?php echo $chara['CharacterId']; ?>'" value="詳細" class="btn btn-info">
                        <?php } ?>
                    </td>
                    <td>
                        <?php if ($chara['IsModify'] == '1') { ?>
                            <input type="button" onclick="location.href='./chara_modify.php?character_id=<?php echo $chara['CharacterId']; ?>&character_sub_id=<?php echo $chara['CharacterSubId']; ?>'" value="編集" class="btn btn-warning">
                        <?php } ?>
                    </td>
                </tr>
            <?php } ?>
        </table>
        <br>
        <input type="button" onclick="location.href='./index.php'" value="戻る" class="btn btn-primary">
	</div>

	<!-- Optional JavaScript -->
	<!-- jQuery first, then Popper.js, then Bootstrap JS -->
	<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
	<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>