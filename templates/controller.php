<?php

// add include


$view = new Template();
$view->title = "hello, world";
$view->links = array("one", "two", "three");
$view->body = "Hi, sup";
$view->content = $view->render('content.tpl.php');
echo $view->render('main.tpl.php'); 
