<?php require_once("./character_list.inc"); ?>
<!doctype html>
<html lang="ja">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
<script src="https://www.w3schools.com/lib/w3.js"></script>
<script type="text/javascript">
</script>

<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../../common.css">
    <title>全キャラ一覧</title>
</head>

<body>
    <div class="container">
        <table class="sorttbl" id="myTable" border="1">
            <thead>
                <tr>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(1)')">No.<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(2)')">SubId.<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(3)')">名前<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(4)')">ひらがな<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(5)')">体重体重<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(6)')">移動速度<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(7)')">急降下速度<i class="fa fa-sort"></i></th>
                    <th style="position: sticky; top: 0;" onclick="w3.sortHTML('#myTable','.item', 'td:nth-child(8)')">落下速度<i class="fa fa-sort"></i></th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($data as $chara) { ?>
                    <tr class="item">
                        <td><?php echo substr('00' . $chara['CharacterId'], -2); ?></td>
                        <td><?php echo $chara['CharacterSubId']; ?></td>
                        <td><?php echo $chara['CharacterName']; ?></td>
                        <td><?php echo $chara['CharacterNameHiragana']; ?></td>
                        <td><?php echo $chara['CharacterWeight']; ?></td>
                        <td><?php echo $chara['CharacterMovingSpeed']; ?></td>
                        <td><?php echo $chara['CharacterSwoopSpeed']; ?></td>
                        <td><?php echo $chara['CharacterFallSpeed']; ?></td>
                    </tr>
                <?php } ?>
            </tbody>
        </table>
        <br />
        <input type="button" onclick="location.href='../index.php'" value="戻る" class="btn btn-primary">
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>