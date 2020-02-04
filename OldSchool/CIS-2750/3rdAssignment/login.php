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
			<div>
				<div class="login-background">
				    <div class="login">
				        <h1>Login</h1>
				        <form class="" action="index.php" method="post">
				            <input required autofocus autocomplete="off" type="text" name="username" placeholder="username"><br><br>
				            <input type="submit" name="login" value="submit">
				        </form>
				    </div>
				</div>

			</div>
		</body>
	</html>