(function($){
$(document).ready(function(){
  $("#edit-wrapper-import-import-button").hide();
});
})(jQuery);

(function ($) {
	$(document).ajaxComplete(function(event,request, settings) {
		if( $("#edit-wrapper-import-myfile-remove-button").length ) {
		  $("#edit-wrapper-import-import-button").click();
		};
	});
}(jQuery));