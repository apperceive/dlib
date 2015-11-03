// Include gulp
const gulp = require('gulp');

// Plugins
const shell = require('gulp-shell');   // use core run instead?
const phplint = require('phplint').lint;

/*
const changed = require('gulp-changed');
const concat = require('gulp-concat');
const notify = require('gulp-notify');
const rename = require('gulp-rename');
var replace = require('gulp-replace');
 bower = require('gulp-bower');
var jade = require('gulp-jade');
var data = require('gulp-data');
const del = require('del');
var path = require('path');
*/

var config = {
  //sassPath: './resources/sass',
  bowerDir: './bower_components'
}

gulp.task('bower', function() {
  return bower()
    .pipe(gulp.dest(config.bowerDir))
});


gulp.task('icons', function() {
  return gulp.src(config.bowerDir + '/fontawesome/fonts/**.*')
    .pipe(gulp.dest('./public/fonts'));
});




// how get @site and content type set or passed in?
 
// TODO: move to array of paths
var genSrc = './build/*/**/*',
    genDst = './src/generated/'
    tplSrc = './templates'
    ;
 
gulp.task('generate-classes', function () {
  gulp.src(genSrv)           // Get input files, each is variable 'file' (an object?)
    .pipe(run(file))                 // TODO: CHANGE THIS
    .pipe(gulp.dest(genDest . '/file.class.inc'))  // TODO: only pass dest folder?
});

gulp.task('phplint', function(cb) {
  // todo: make string a var named phpSrc
  phplint(['src/**/*.inc, templates/*.+(php|inc)'], {limit: 10}, function (err, stdout, stderr) {
    if (err) {
      cb(err)
      process.exit(1)
    }
    cb()
  })
});

// var watcher = gulp.watch('js/**/*.js', ['uglify','reload']);
// watcher.on('change', function(event) {
  // console.log('File ' + event.path + ' was ' + event.type + ', running tasks...');
// });



// gulp.watch('js/**/*.js', function(event) {
  // console.log('File ' + event.path + ' was ' + event.type + ', running tasks...');
// });

gulp.task('jade', function() {
    return gulp.src('src/templates/**/*.jade')
        .pipe(jade()) // pip to jade plugin
        .pipe(gulp.dest('builds/development')); // tell gulp our output folder
});


// default gulp task
gulp.task('default', ['generate-classes', 'phplint'], function() {
  // watch for both script and template changes
  gulp.watch('./src/*.html', ["htmlpage"]);

});

