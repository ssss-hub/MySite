<?php require_once("./detail.inc"); ?>
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
    <title>詳細画面</title>
</head>

<body>
    <div class="container">
        <h1>詳細画面</h1>
        <h2><?php echo $recipe['RecipeName']; ?></h2>
        <?php if ($recipe['CompletedPhotoUrl'] != '') { ?>
            <img src="<?php echo $recipe['CompletedPhotoUrl']; ?>" alt="完成写真" title="<?php echo $recipe['RecipeName']; ?>" style="width:100%; max-width: 100%; height: auto;" >
        <?php } ?>
        <h3>材料</h3>
        <?php foreach ($recipe['material'] as $material) { ?>
            <div class="checkbox">
                <label>
                    <input type="checkbox"><?php echo $material['MaterialName']; ?>・・・<?php echo ($material['Quantity'] == 0) ? '' : round($material['Quantity'], 1); ?><?php echo $material['Unit']; ?>
                </label>
            </div>
        <?php } ?>
        <h3>材料掛け算</h3>
        <form name="search" action="detail.php" method="POST">
            <div class="form-group">
                <input type="hidden" name="recipe_id" value="<?php echo $recipeId; ?>">
                <div class="col-sm-2">
                    <input type="text" name="fraction1" value="<?php echo $fraction1; ?>" inputmode="numeric" pattern="\d*" placeholder="分子" class="form-control" />
                </div>
                <div class="col-sm-2">
                    /
                </div>
                <div class="col-sm-2">
                    <input type="text" name="fraction2" value="<?php echo $fraction2; ?>" inputmode="numeric" pattern="\d*" placeholder="分母" class="form-control" />
                </div>
                <div class="col-sm-2">
                    <input type="submit" name="fraction" value="計算" class="btn btn-success" />
                </div>
            </div>
        </form>
        <h3>調理工程</h3>
        <ol>
            <?php foreach ($recipe['process'] as $process) { ?>
                <li>
                    <?php echo $process['ProcessContent']; ?>
                    <?php if ($process['ProcessPhotoUrl'] != '') { ?>
                        <br>
                        <img src="<?php echo $process['ProcessPhotoUrl']; ?>" alt="行程写真" title="<?php echo $process['ProcessContent']; ?>" style="width:100%; max-width: 100%; height: auto;" >
                    <?php } ?>
                </li>
            <?php } ?>
        </ol>
        <?php if (Count($recipe['point']) > 0) { ?>
            <h3>コツ・ポイント</h3>
            <ul>
                <?php foreach ($recipe['point'] as $point) { ?>
                    <li>
                        <?php echo $point['PointContent']; ?>
                    </li>
                <?php } ?>
            </ul>
        <?php } ?>
        <?php if ($recipe['ReferenceUrl'] != '') { ?>
            <h3>URL</h3>
            <label>
                <?php echo $recipe['ReferenceUrl']; ?>
            </label>
        <?php } ?>
        <br>
        <input type="button" onclick="location.href='./search.php'" value="戻る" class="btn btn-primary">
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>