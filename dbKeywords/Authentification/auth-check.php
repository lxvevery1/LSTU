<?php
// ����������� � ���� ������
$mysqli = new mysqli("localhost", "root", "", "authentificationdb");

// �������� ����������� � ���� ������
if ($mysqli->connect_errno) {
    die("Error: " . $mysqli->connect_error);
}

// ������� �������� �������������� ������������
function isUserAuthenticated() {
    return isset($_SESSION["id"]);
}

// ������� ��������, �������� �� ������������ ���������������
function isUserAdmin() {
    global $mysqli;

    if (isUserAuthenticated()) {
        $userId = $_SESSION["id"];
        $query = "SELECT admin FROM user WHERE id = '$userId'";

        if ($result = $mysqli->query($query)) {
            $row = $result->fetch_assoc();
            $admin = $row["admin"];

            // ��������, �������� �� ������������ ���������������
            return $admin == 1;
        }
    }

    return false;
}

if (!isUserAuthenticated()){
    header("Location: http://localhost/dbKeywords/Authentification/index.php");
    exit;
}

?>