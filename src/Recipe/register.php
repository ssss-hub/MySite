<?php require_once("./register.inc"); ?>
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
    <title>登録画面</title>
</head>

<body>
    <div class="container">
        <h1>登録画面</h1>
        <form name="search" action="register.php" method="POST">
            <h2>料理名</h2>
            <table class="table table-striped table-bordered">
                <tr>
                    <th><font color="blue">料理名</font></th>
                    <th><font color="blue">料理名ひらがな</font></th>
                    <th>完成写真URL</th>
                    <th>参考記事URL</th>
                </tr>
                <tr>
                    <td>
                        <input type="text" name="recipeName" />
                    </td>
                    <td>
                        <input type="text" name="recipeNameHiragana" />
                    </td>
                    <td>
                        <input type="text" name="completedPhotoUrl" />
                    </td>
                    <td>
                        <input type="text" name="referenceUrl" />
                    </td>
                </tr>
            </table>
            <h2>材料</h2>
            <table class="table table-striped table-bordered">
                <tr>
                    <th><font color="blue">材料名</font></th>
                    <th><font color="blue">材料名ひらがな</font></th>
                    <th>数量</th>
                    <th>単位</th>
                </tr>
                <?php for ($i = 0; $i < 15; $i++) { ?>
                    <tr>
                        <td>
                            <input type="text" name="material[<?php echo $i; ?>][materialName]" />
                        </td>
                        <td>
                            <input type="text" name="material[<?php echo $i; ?>][materialNameHiragana]" />
                        </td>
                        <td>
                            <input type="text" name="material[<?php echo $i; ?>][quantity]" />
                        </td>
                        <td>
                            <input type="text" name="material[<?php echo $i; ?>][unit]" value="g" />
                        </td>
                    </tr>
                <?php } ?>
            </table>
            <h2>調理工程</h2>
            <table class="table table-striped table-bordered">
                <tr>
                    <th><font color="blue">行程内容</font></th>
                    <th>行程写真URL</th>
                </tr>
                <?php for ($i = 0; $i < 20; $i++) { ?>
                    <tr>
                        <td>
                            <input type="text" name="process[<?php echo $i; ?>][processContent]" />
                        </td>
                        <td>
                            <input type="text" name="process[<?php echo $i; ?>][processPhotoUrl]" />
                        </td>
                    </tr>
                <?php } ?>
            </table>
            <h2>コツ・ポイント</h2>
            <table class="table table-striped table-bordered">
                <tr>
                    <th>コツ・ポイント内容</th>
                </tr>
                <?php for ($i = 0; $i < 10; $i++) { ?>
                    <tr>
                        <td>
                            <input type="text" name="point[<?php echo $i; ?>][pointContent]" />
                        </td>
                    </tr>
                <?php } ?>
            </table>
            <br>
            <input type="submit" name="register" value="登録" class="btn btn-success" />
            <input type="button" onclick="location.href='../index.php'" value="戻る" class="btn btn-primary offset-1">
        </form>
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>