if (Drupal.jsEnabled) {
  $(document).ready(function() {
		
    $("a.actie-link").click(function() {
  	  var resultaat = function(data) {
	     var result = Drupal.parseJson(data);
		 var elem = result['elem_id'];
		 var newStatus = result['div_status'];
		 // Vinkje of Kruisje
		 $('#aan-widget-' + elem).attr('Class', result['div_status']);
		// $('#link-ja-' + elem).css('display', result['ja_display_attr']); 
		// $('#link-nee-' + elem).css('display', result['nee_display_attr']);
	  }
	  
	  $.get(this.href, null, resultaat);
	  return false;
      });
	
	
	
 

	
	

    $("a.bt_print_link").click(function() {
      var pagina = function(data) {
				var paginaResult = Drupal.parseJson(data);
	      var pText = paginaResult['text'];
				var windowSettings = 'toolbar=no,location=no,' +'status=no,menu=no,scrollbars=yes,width=650,height=400';
        printerWindow = window.open('', '', windowSettings);
        printerWindow.document.open();
        printerWindow.document.write(pText);
        printerWindow.document.close();
        printerWindow.print();

			
			
			
			
			
	  }
	  $.get(this.href, null, pagina);
	  
	  return false;
    });

  });

}
