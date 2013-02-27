// JavaScript Document

if (Drupal.jsEnabled) {
  $(document).ready(function() {
	  
	  
    $('a.reactie-buttons-button').click(function() {
      var resultaat = function(data) {
        var result = Drupal.parseJson(data);
		var new_status = result['new_status'];
		var reactie_text = result['reactie_text'];
		var id = result['id'];
		console.log(id);
		$('.reactie-balk-text').text(reactie_text);
		if (new_status == 'ja') {
		  $('#reactie-balk-ja').hide();
		  $('#reactie-balk-nee').hide();
		  $('#reactie-balk-vraagteken').hide();
		}
		if (new_status == 'nee') {
		  $('#reactie-balk-ja').show();
		  $('#reactie-balk-nee').hide();
		  $('#reactie-balk-vraagteken').show();
		}
		if (new_status == 'vraagteken') {
		  $('#reactie-balk-ja').show();
		  $('#reactie-balk-nee').show();
		  $('#reactie-balk-vraagteken').hide();
		}
		$('#podium-link-' + id).attr('Class', new_status);
	  }
	  $.get(this.href, null, resultaat);
	  return false;
      });
	  
	  	  
    $("a.podium-link-actie").click(function() {
  	  var resultaat = function(data) {
	     var result = Drupal.parseJson(data);
		 var id = result['id'];
		 var stage_text = result['stage_text'];
		 if (stage_text == '') {
			 stage_text = '\xa0';
		 }
		 $('#podium-link-'+ id ).text(stage_text);
         //alert('stage_text');
	  }
	  $.get(this.href, null, resultaat);
	  return false;
      });
	
	
	


  });

}
