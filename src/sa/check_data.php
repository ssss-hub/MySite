<?php require_once("./check_data.inc"); ?>
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
    <title>データチェック</title>
</head>
<body>
    <!-- <div class="container"> -->
    <div>
        <h1>データ</h1>
        <input type="button" onclick="location.href='index.php'" value="戻る" class="btn btn-primary">
        <table border="1" style="width: 100%;">
            <tbody>
                <tr>
                    <th>No.</th>
                    <?php echo isset($data_list[0]['PageId']) ? '<th>PageId</th>' : '' ?>
                    <!-- <?php //echo isset($data_list[0]['PageUrl']) ? '<th>PageUrl</th>' : '' ?> -->
                    <?php echo isset($data_list[0]['PageTitle']) ? '<th>PageTitle</th>' : '' ?>
                    <?php echo isset($data_list[0]['PageStatus']) ? '<th>PageStatus</th>' : '' ?>
                    <?php echo isset($data_list[0]['UrlCount']) ? '<th>UrlCount</th>' : '' ?>
                    <?php echo isset($data_list[0]['UrlId']) ? '<th>UrlId</th>' : '' ?>
                    <!-- <?php //echo isset($data_list[0]['Url']) ? '<th>Url</th>' : '' ?> -->
                    <?php echo isset($data_list[0]['FileName']) ? '<th>FileName</th>' : '' ?>
                    <?php echo isset($data_list[0]['FileStatus']) ? '<th>FileStatus</th>' : '' ?>
                    <?php echo isset($data_list[0]['FileSize']) ? '<th>FileSize</th>' : '' ?>
                    <?php echo isset($data_list[0]['FileHeight']) ? '<th>FileHeight</th>' : '' ?>
                    <?php echo isset($data_list[0]['FileWidth']) ? '<th>FileWidth</th>' : '' ?>
                    <?php echo isset($data_list[0]['UpdateDate']) ? '<th>UpdateDate</th>' : '' ?>
                </tr>
                <td style="word-break : break-all;">
                <!-- <td> -->
                    <?php foreach ($data_list as $index => $data) { ?>
                        <tr>
                            <td><?php echo strval($index + 1); ?></td>
                            <?php echo isset($data_list[0]['PageId']) ? '<td>' . $data['PageId'] . '</td>' : '' ?>
                            <!-- <?php //echo isset($data_list[0]['PageUrl']) ? '<td>' . $data['PageUrl'] . '</td>' : '' ?> -->
                            <?php echo isset($data_list[0]['PageTitle']) ? '<td>' . $data['PageTitle'] . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['PageStatus']) ? '<td>' . $data['PageStatus'] . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['UrlCount']) ? '<td>' . $data['UrlCount'] . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['UrlId']) ? '<td>' . $data['UrlId'] . '</td>' : '' ?>
                            <!-- <?php //echo isset($data_list[0]['Url']) ? '<td>' . $data['Url'] . '</td>' : '' ?> -->
                            <?php echo isset($data_list[0]['FileName']) ? '<td>' . $data['FileName'] . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['FileStatus']) ? '<td>' . $data['FileStatus'] . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['FileSize']) ? '<td>' . number_format($data['FileSize']) . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['FileHeight']) ? '<td>' . number_format($data['FileHeight']) . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['FileWidth']) ? '<td>' . number_format($data['FileWidth']) . '</td>' : '' ?>
                            <?php echo isset($data_list[0]['UpdateDate']) ? '<td>' . $data['UpdateDate'] . '</td>' : '' ?>
                        </tr>
                    <?php } ?>
                </td>
            </tbody>
        </table>
        <input type="button" onclick="location.href='index.php'" value="戻る" class="btn btn-primary">
    </div>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>