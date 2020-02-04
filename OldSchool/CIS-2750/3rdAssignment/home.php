<?PHP
	if (isset($_GET['login'])){
		$username = $_GET['username'];
		$textArea = "Please select a stream to start!";
	} else if (isset($_POST['changeStream'])){
		$currentPost = getLastPost($_GET['stream']);
		load($_GET['username'],$_GET['stream'],none);		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream'],$currentPost,"date");
	} else if (isset($_POST['nextPost'])){
		$currentPost = $_GET['currPost'] + 1;
		if ($currentPost > getLastPost($_GET['stream'])) $currentPost = $_GET['currPost'];
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);
	} else if (isset($_POST['lastPost'])){
		$currentPost = $_GET['currPost'] -1;
			if ($currentPost <= 0) $currentPost = 1;
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);
	} else if (isset($_POST['checkForNew'])){
		load($_GET['username'],$_GET['stream'],none);		$textArea = updateViewer($_GET['username'],$_GET['stream'],$_GET['currPost']);
		updateUserFile($_GET['username'],$_GET['stream'],$currentPost,$_GET['sort']);
	} else if (isset($_POST['markAll'])){
		exec("./2ndAssignment/viewAPI.py markAll ".$_GET['username']." ".$_GET['stream'],$output,$status);
		$currentPost = getLastPost($_GET['stream']);
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
	} else if (isset($_POST['toggle'])){
	}

	function get($form){
		$paramList = "?";
		foreach ($form as $key => $value) {
			$paramList .= "&".$key."=".$value;
		}
		return $paramList;
	}

	function getLastPost($streamName) {
		exec("./2ndAssignment/viewAPI.py getLastRead ".$_GET['username']." ".$streamName,$output,$status);
		if ($status) {
			echo "Get last Post ".$status;
		}
		return ( (int)$output[0] );
	}

	function load($username,$streamName,$sort){
		exec("./2ndAssignment/viewAPI.py loadPosts ".$username." ".$streamName." ".$sort,$output,$status);
	}

	function updateUserFile($username,$streamName,$currentPost,$sort) {
		if ($streamName != "All" and $sort != "name") {
echo $currentPost;
			exec("./2ndAssignment/viewAPI.py updateUserFile ".$username." ".$streamName,$output,$status);
			if ($status) {
				echo "Update user Stream ".$status;
			}
		}
	}

	function updateViewer($username,$streamName,$currentPost) {
		exec("./2ndAssignment/viewAPI.py getPost ".$username." ".$currentPost,$textArea,$status);
		if ($status) {
			echo " update Viewer ".$status;
		}
		return $textArea;
	}

	function formatPost($post) {
		if ($post[0] == 'P')
			echo $post;
		else {
			$index = 3;
			echo $post[0]."\n";
			echo $post[1]."\n";
			echo $post[2]."\n";
			while ($post[$index][0] == '-') {
				echo $post[$index]."\n";
				$index++;
			}
		}
}

?>
<!DOCTYPE html>
	<html>
		<head>
			<meta charset="utf-8">
			<title>Assignment 3</title>
			<link rel="stylesheet" type="text/css" href="styles.css">
		</head>

		<body>
			<br>
			<hr>
			<div>
				<div class="dropdown">
				    <button class="UpperButton">Streams</button>
				    <div class="dropdown-content">
				        <?php
				            exec('./2ndAssignment/viewAPI.py getStreams '.$_GET['username'],$output,$status);
				            if ($status){
				                echo $status;
				            }
				            if ($output[0] == "Create Stream"){
				                echo "<form action=\""."index.php?username=".$_GET['username']."\" "."method=\"post\">";
				                echo    "\t<input class=\"dropdownlink\" type=\"submit\" name=\"gotoaddauthor\" value=\"Create Stream\">";
				                echo "</form>";
				            } else {
				                foreach ($output as $line) {
				                    echo "<form action=\""."home.php?username=".$_GET['username']."&stream=".$line."&sort=date\" "."method=\"post\">";
				                    echo    "\t<input class=\"dropdownlink\" type=\"submit\" name=\"changeStream\" value=\"".$line."\">";
				                    echo "</form>";
				                }
				            }
				        ?>
				    </div>
				</div>

			</div>
			<br>
			<form class="buttonForm" method="POST"action="login.php">
				<input  class="UpperButton" type="submit" value="Change Author" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo 'index.php'.get($_GET) ?>">
				<input  class="UpperButton" type="submit" name="gotoaddauthor" value="Add or Remove Author" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo 'index.php'.get($_GET) ?>">
				<input  class="UpperButton" type="submit" name="gotopost" value="Post" >
			</form>
			<br>
			<br>
			<div>
				<div class="viewWindowCover center">
				    <textarea class="viewWindow" rows="24" cols="80" readonly ><?PHP echo formatPost($textArea) ?></textarea>
				</div>

			</div>
			<br>
			<form class="buttonForm" method="POST"action="<?PHP echo $PHP_SELF; ?>">
				<input  class="UpperButton" type="submit" name="toggle" value="Toggle Sorting" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo $PHP_SELF; ?>">
				<input  class="UpperButton" type="submit" name="markAll" value="Mark All As Read" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo $PHP_SELF; ?>">
				<input  class="UpperButton" type="submit" name="checkForNew" value="Check For New Posts" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo $PHP_SELF.get($_GET).'&currPost='.$currentPost ?>">
				<input  class="UpperButton" type="submit" name="nextPost" value="Next Post" >
			</form>
			<form class="buttonForm" method="POST"action="<?PHP echo $PHP_SELF.get($_GET).'&currPost='.$currentPost ?>">
				<input  class="UpperButton" type="submit" name="lastPost" value="Previous Post" >
			</form>
			<hr>
		</body>
	</html>