var run = require('gulp-run');
 

 // how get @site and content type set or passed in?
 
var genSrc = './build/*/**/*',
    genDst = './src/generated/'
    tplSrc = './'
    tplDest = ''
    ;
 
gulp.task('generate-classes', function () {
      
  gulp.src(genSrv)           // Get input files, each is variable 'file'
    .pipe(run(file)) 
    .pipe(gulp.dest(genDest . '/file.class.inc'))  // only pass dest folder?
});




// default gulp task
gulp.task('default', ['generate-classes'], function() {
  // watch for both script and template changes
  gulp.watch('./src/*.html', ["htmlpage"]);

});

