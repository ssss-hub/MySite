<?php require_once("./select_detail.inc"); ?>
<!doctype html>
<html lang="ja">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
<script type="text/javascript">
    var cnt = 0;
    var urlList = [];
    <?php foreach ($data as $index => $photo) { ?>
        urlList[<?php echo $index; ?>] = '<?php echo $photo['PageId'] . '_' . $photo['UrlId']; ?>';
    <?php } ?>
    $(document).ready(
        function() {
            $('#img_' + cnt).show();

            windowHeight = $(window).height();
            windowWidth = $(window).width();
            imgHeight = $('#img_' + cnt).height();
            imgWidth = $('#img_' + cnt).width();
            if (imgHeight * windowWidth < imgWidth * windowHeight) {
                $('#img_' + cnt).css('width', windowWidth + 'px');
            } else {
                $('#img_' + cnt).css('height', windowHeight + 'px');
            }
        }
    );

    function ToRight() {
        $('#img_' + cnt).hide();
        cnt = cnt + 1;
        $('#img_' + cnt).show();

        if (cnt == <?php echo Count($data); ?>) {
            cnt = -1;
            $('#button').show();
        } else {
            $('#button').hide();
        }

        windowHeight = $(window).height();
        windowWidth = $(window).width();
        imgHeight = $('#img_' + cnt).height();
        imgWidth = $('#img_' + cnt).width();
        if (imgHeight * windowWidth < imgWidth * windowHeight) {
            $('#img_' + cnt).css('width', windowWidth + 'px');
        } else {
            $('#img_' + cnt).css('height', windowHeight + 'px');
        }
    };

    function ToLeft() {
        $('#img_' + cnt).hide();
        cnt = cnt - 1;
        $('#img_' + cnt).show();

        if (cnt == -1) {
            cnt = <?php echo Count($data); ?>;
            $('#button').show();
        } else {
            $('#button').hide();
        }

        windowHeight = $(window).height();
        windowWidth = $(window).width();
        imgHeight = $('#img_' + cnt).height();
        imgWidth = $('#img_' + cnt).width();
        if (imgHeight * windowWidth < imgWidth * windowHeight) {
            $('#img_' + cnt).css('width', windowWidth + 'px');
        } else {
            $('#img_' + cnt).css('height', windowHeight + 'px');
        }
    };
    $(document).keydown(
        function(e) {
            if (e.keyCode == 39) { // 39・・・「→」
                ToRight();
            }
            if (e.keyCode == 37) { // 37・・・「←」
                ToLeft();
            }
            if (e.keyCode == 83) { // 83・・・「s」
                $('input[name="choice[' + urlList[cnt] + ']"]')[0].checked = true; //保存のラジオボタンにチェックを付ける
            }
            if (e.keyCode == 68) { // 68・・・「d」
                $('input[name="choice[' + urlList[cnt] + ']"]')[1].checked = true; //削除のラジオボタンにチェックを付ける
                // alert('削除にチェックしました');
            }
            if (e.keyCode == 82) { // 82・・・「r」
                $('input[name="register"]').click(); //登録ボタンを押す
            }
        }
    );
    $(document).on('click', function() {
        if (event.pageX * 2 < $(window).width()) {
            ToLeft();
        } else {
            ToRight();
        }
    });
</script>


<head>
    <meta name="robots" content="noindex">
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">

    <link rel="stylesheet" href="../common.css">
    <title><?php echo (@$title != NULL) ? $title : '通過'; ?></title>
</head>

<body>
    <form name="select_detail" action="select_detail.php" method="POST">
        <div style="text-align : center">
            <?php foreach ($data as $index => $photo) { ?>
                <?php if (@$_GET['okOnly'] != NULL) { ?>
                    <img src="./Download/<?php echo $photo['FileName']; ?>" id="img_<?php echo $index; ?>" style="display:none">
                <?php } else { ?>
                    <img src="<?php echo $photo['Url']; ?>" id="img_<?php echo $index; ?>" style="display:none">
                <?php } ?>
                <div style="display:none;">
                    <?php echo $photo['PageTitle']; ?>
                </div>
            <?php } ?>
        </div>
        <div class="container">
            <?php foreach ($data as $index => $photo) { ?>
                <input type="radio" name="choice[<?php echo $photo['PageId'] . '_' . $photo['UrlId']; ?>]" value="save" <?php echo (@$_GET['okOnly'] != NULL) ? 'checked' : ''; ?> style="display:none">
                <input type="radio" name="choice[<?php echo $photo['PageId'] . '_' . $photo['UrlId']; ?>]" value="delete" <?php echo (@$_GET['okOnly'] != NULL) ? '' : 'checked'; ?> style="display:none">
            <?php } ?>
            <div id="button" style="display:none">
                <input type="hidden" name="sort" value="<?php echo $_GET['sort']; ?>">
                <input type="submit" name="register" value="登録" class="btn btn-success" />
                <input type="button" onclick="location.href='<?php echo (@$_GET['okOnly'] != NULL) ? 'index.php' : 'select.php?sort=' . $_GET['sort']; ?>'" value="戻る" class="btn btn-primary offset-1">
            </div>
        </div>
    </form>

    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>

</html>