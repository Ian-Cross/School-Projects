<?PHP
    if (isset($_POST['login']) && $_POST['username'] != "") {
        gohome($_POST);
    } else if (isset($_POST['gotoaddauthor'])) {
        $file = fopen("addauthor.php","w");
        exec('./a3 addauthor.wpml',$output,$status);
        if ($status){
            echo $status;
        }
        fwrite($file,implode("\n",$output));
        header("Location:addauthor.php?username=".$_GET['username']);
    } else if (isset($_POST['gotopost'])) {
        if (isset($_GET['stream'])){
            $file = fopen("post.php","w");
            exec('./a3 post.wpml',$output,$status);
            if ($status){
                echo $status;
            }
            fwrite($file,implode("\n",$output));
            header("Location:post.php?".get($_GET));
        } else {
            gohome($_GET);
        }
    } else if (isset($_POST['addauthor'])) {
        $file = fopen("AddAuthor.new","w");
        fwrite($file,implode("\n",$_POST));
        exec('./2ndAssignment/addauthor',$output,$status);
        if ($status){
            echo $status;
        }
        gohome($_GET);
    } else if (isset($_POST['makepost'])) {
        $file = fopen("Post.new","w");
        fwrite($file,implode("\n",$_POST));
        exec('./2ndAssignment/post',$output,$status);
        if ($status){
            echo $status;
        }
        gohome($_GET);
    } else if (isset($_POST['goBack'])) {
        header("Location:home.php?username=".$_GET['username']."&login=submit");
    } else {
        $file = fopen("login.php","w");
        exec('./a3 login.wpml',$output,$status);
        if ($status){
            echo $status;
        }
        fwrite($file,implode("\n",$output));
        header("Location:login.php?");
    }

    function gohome($URL){
        $file = fopen("home.php","w");
        exec('./a3 home.wpml',$output,$status);
        if ($status){
            echo $status;
        }
        fwrite($file,implode("\n",$output));
        header("Location:home.php?".get($URL));
    }

    function get($form){
        $paramList = "";
        foreach ($form as $key => $value) {
            $paramList .= "&".$key."=".$value;
        }
        return $paramList;
    }

    function isUserinStream($username,$stream) {
        exec("./2ndAssignment/libAPI isUserInStream ".$username." ".$stream,$output,$status);
        if ($status){
            echo $status;
        } else {
            if ($output[0] != 1){
                echo $output[0];
                exec("./2ndAssignment/libAPI addUser ".$username." ".$stream);
            }
        }
    }

    function addUser($username,$stream){
        exec("./2ndAssignment/libAPI addUser ".$username." ".$stream,$output,$status);
        if ($status){
            echo $status;
        }
    }

    function messagePop($message){

    }
?>
