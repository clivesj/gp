(function($) {
  $(document).ready(function() {
    $('h1').click(function() {
      alert('test');
    });

    $("a.actie-link").click(function() {
      //var elem = Drupal.settings.repetitie.elem_id;
      //var resultaat = function(data) {
      //var result = Drupal.parseJson(data);
      //var elem = result['elem_id'];
      var newStatus = Drupal.settings.repetitie.div_status;
      // Vinkje of Kruisje
     $('#aan-widget-' + Drupal.settings.repetitie.elem_id).attr('Class', Drupal.settings.repetitie.div_status);
      // $('#link-ja-' + elem).css('display', Drupal.settings.repetitie.ja_display_attr']);
      // $('#link-nee-' + elem).css('display', result['nee_display_attr']);
      alert(newStatus);
      alert('#aan-widget-' + Drupal.settings.repetitie.elem_id);

    });

  });
}) (jQuery);
