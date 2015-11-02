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
const del = require('del');

*/



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


// default gulp task
gulp.task('default', ['generate-classes', 'phplint'], function() {
  // watch for both script and template changes
  gulp.watch('./src/*.html', ["htmlpage"]);

});

