# dlib
drupal object lib

Experimental code to generate PHP classes for simplifying use of Drupal content types.

First pass is to mainly encapsulate and hide all array index checking and error handling, allowing code like the following, hich loads a node, gets it's title and an array of multifield objects containing multifield values, indexed by their corresponding fieldnames:

`$nd = new nodeClass(207);`

`$t = $nd->get('title');`

`$arr = $nd->get('field_project_observers');`

Multifields and unlimited field lists are supported (to one level and within the limits of multifields).

Works with Drupal 7 and Drush 6 and 7.

Example command (for now):  

`drush @alias scr test/drush/node.class.test.drush`

where @alias is a drush alias.
