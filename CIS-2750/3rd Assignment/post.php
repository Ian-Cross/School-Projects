<?PHP
	if (isset($_GET['login'])){
		$username = $_GET['username'];
		$textArea = "Please select a stream to start!";
	} else if (isset($_POST['changeStream'])){
		$currentPost = getLastPost($_GET['stream']);
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream']);
	} else if (isset($_POST['nextPost'])){
		$currentPost = $_GET['currPost'] + 1;
		if ($currentPost >= getLastPost($_GET['stream'])) $currentPost = $_GET['currPost'];
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream']);
	} else if (isset($_POST['lastPost'])){
		$currentPost = $_GET['currPost'] - 1;
		if ($currentPost < 0) $currentPost = 0;
		$textArea = updateViewer($_GET['username'],$_GET['stream'],$currentPost);
		updateUserFile($_GET['username'],$_GET['stream']);
	} else if (isset($_POST['checkForNew'])){
	} else if (isset($_POST['markAll'])){
		exec("./2ndAssignment/viewAPI.py markAll ".$_GET['username']." ".$_GET['stream'],$output,$status);
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
		return (int)$output[0];
	}

	function updateUserFile($username,$streamName) {
		exec("./2ndAssignment/viewAPI.py updateUserFile ".$username." ".$streamName,$output,$status);
		if ($status) {
			echo "Update user Stream ".$status;
		}
	}

	function updateViewer($username,$streamName,$currentPost) {
		exec("./2ndAssignment/viewAPI.py getPost ".$username." ".$streamName." ".$currentPost,$textArea,$status);
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
			<br>
			<hr>
			<br>
			<div>
				<div class="post">
				    <form class="postbackground" action="<?PHP echo 'index.php'.get($_GET).'&login=submit'; ?>" method="post">
				        <h1>Make a Post </h1>
				        <input type="hidden" name="username" value="<?PHP echo $_GET['username'];?>">
				        <input type="hidden" name="stream" value="<?PHP echo $_GET['stream'];?>">
				        <h3><?PHP echo 'as '.$_GET['username'].' into the '.$_GET['stream'].' stream'; ?><h3>
				        <textarea class="postArea" name="postArea" rows="24" cols="80"></textarea><br>
				        <input class="UpperButton" type="submit" name="goBack" value="Back">
				        <input class="UpperButton" type="submit" name="makepost" value="Post">
				    </form>
				</div>

			</div>
			<br>
			<hr>
		</body>
	</html>