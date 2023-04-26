<!DOCTYPE html>
<html>
<head>
	<title>Weather Site</title>
	<style>
		table.long {
			border-collapse: collapse;
			width: 100%;
		}
		table.long th,
		table.long td {
			padding: 8px;
			text-align: left;
			border-bottom: 1px solid #ddd;
		}
		table.short {
			border-collapse: collapse;
			width: 100%;
		}
		table.short th,
		table.short td {
			padding: 8px;
			text-align: center;
			border-right: 1px solid #ddd;
		}
		table.short td:last-child,
		table.short th:last-child {
			border-right: none;
		}
		table.short td:hover{
			background-color: #f5f5f5;
        }
		table.long tr:hover {
			background-color: #f5f5f5;
		}
	</style>
</head>
<body>
<h1>Weather Site</h1>
	<?php
	session_start();
    $cnx = new mysqli('localhost', 'user', 'Password', 'weather');
        
    if ($cnx->connect_error) {
        die('Connection failed: ' . $cnx->connect_error);
    }

    $table_exists_sql = "SHOW TABLES LIKE 'user_data'";
    $result = $cnx->query($table_exists_sql);
    $table_exists = $result->num_rows > 0;

    if (!$table_exists) {
        $create_table_sql = "CREATE TABLE user_data (
            ip_address VARCHAR(50) PRIMARY KEY,
            city VARCHAR(50) NOT NULL
        )";
        $cnx->query($create_table_sql);
    }

    $current_ip = $_SERVER['REMOTE_ADDR'];
    $check_ip_sql = "SELECT * FROM user_data WHERE ip_address='$current_ip'";
    $result = $cnx->query($check_ip_sql);
    $ip_exists = $result->num_rows > 0;
	if (isset($_POST['submit'])){
		$cityReplace = $_SESSION['city'];

        if ($ip_exists) { 
            $update_sql = "UPDATE user_data SET city='$cityReplace' WHERE ip_address='$current_ip'";
            $cnx->query($update_sql);
        } else {
            $add_sql = "INSERT INTO user_data (ip_address, city) VALUES ('$current_ip', '$cityReplace')";
            $cnx->query($add_sql);
        } 
    }else if ($ip_exists && $_POST['city'] == "") {
        $row = $result->fetch_assoc();
        $_SESSION['city'] = $row['city'];
    }else if (isset($_POST['city'])) {
		$_SESSION['city'] = $_POST['city'];
	}

	selectForm($cnx, $_SESSION['city']);
	outputCity($cnx, $_SESSION['city']);

	function selectForm($cnx, $city){
		echo "<form method='post'>";
    	echo "<label for='city'>Select a city:</label>";
    	echo "<select name='city' id='city' onchange='this.form.submit()'>";
    	echo "<option value=''>--Select a city--</option>";
    	$sql = "SELECT DISTINCT cityName FROM weather ORDER BY cityName ASC";
    	$result = mysqli_query($cnx, $sql);
    	while ($row = mysqli_fetch_assoc($result)) {
			echo "<option value='" . $row['cityName'] . "'";
			if (isset($_POST['city']) && $_POST['city'] == $row['cityName']) {
				echo " selected";
				$_SESSION['city'] = $row['cityName'];
			} elseif ($city == $row['cityName']) {
				echo " selected";
				$_SESSION['city'] = $row['cityName'];
			}
			echo ">" . $row['cityName'] . "</option>";
    	}
		echo "</select>";
		echo "</form>";
		echo "<form method='post'><input type='submit' name='submit' value='Save Favorite City'></form>";
	}
	function outputCity($cnx, $city){
		$_SESSION['city'] = $city;
		$sql = "SELECT * FROM weather WHERE cityName='$city'";
		$result = mysqli_query($cnx, $sql);
        
		if($row = mysqli_fetch_assoc($result)){
			$statename = $row['stateName'];
			$date = $row['date'];
			$dayOrNight = $row['dayOrNight'];
			$temp = $row['temp'];
			$shortDescriptionPeriodName = $row['shortDescriptionPeriodName'];
			$shortDescription = $row['shortDescription'];
			$shortDescriptionTemp = $row['shortDescriptionTemp'];
			$longDescriptionPeriodName =  $row['longDescriptionPeriodName'];
			$longDescription =  $row['longDescription'];

			echo "<h2>" . $city . ", " . $statename .  " Weather</h2>";
			echo "<h3>" . $date . ", " . $dayOrNight . "</h3>" ;
			echo "<h3>" . $temp . "</h3>" ;

			echo "<h2>Short Description</h2>";
			echo "<table class='short'>";
			echo "<tr>";
			$shortDescriptionPeriodName = str_replace(array("[", "]", "'"), "", $shortDescriptionPeriodName);
			$shortDescriptionPeriodNameArray = explode(", ", $shortDescriptionPeriodName);
			foreach ($shortDescriptionPeriodNameArray as $value) {
				echo "<td>$value</td>";
			}
			echo "</tr>";	
			echo "<tr>";
			$shortDescription = str_replace(array("[", "]", "'"), "", $shortDescription);
			$shortDescriptionArray = explode(", ", $shortDescription);
			foreach ($shortDescriptionArray as $value) {
				echo "<td>$value</td>";
			}
			echo "</tr>";
			echo "<tr>";
			$shortDescriptionTemp = str_replace(array("[", "]", "'"), "", $shortDescriptionTemp);
			$shortDescriptionTempArray = explode(", ", $shortDescriptionTemp);
			foreach ($shortDescriptionTempArray as $value) {
				echo "<td>$value</td>";
			}
			echo "</tr>";
			echo "</table>";
			
			echo "<h2>Long Description</h2>";
			$longDescriptionPeriodName = str_replace(array("[", "]", "'"), "", $longDescriptionPeriodName);
			$longDescriptionPeriodNameArray = explode(", ", $longDescriptionPeriodName);
			$longDescription = str_replace(array("[", "]"), "", $longDescription);
			$longDescription = substr($longDescription, 1, strlen($longDescription)-2);
			$longDescriptionArray = explode("', '", $longDescription);
			echo "<table class='long'>";
			for ($i = 0; $i < count($longDescriptionArray); $i++) {
				echo "<tr>";
				if (isset($longDescriptionPeriodNameArray[$i])) {
					echo "<td>" . $longDescriptionPeriodNameArray[$i] . "</td>";
				} else {
					echo "<td></td>";
				}
				if (isset($longDescriptionArray[$i])) {
					echo "<td>" . $longDescriptionArray[$i] . "</td>";
				} else {
					echo "<td></td>";
				}
				echo "</tr>";
			}
			echo "</table>";
		}
	}
    
	mysqli_close($cnx);
	?>

</body>
</html>
