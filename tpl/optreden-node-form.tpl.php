<div id="optreden-node-form">
  <?php print render($form['title']); ?>
  <?php print render($form['field_status']); ?>
  <div class = 'left-collumn'>
    <?php print render($form['field_datum']); ?>
    <?php print render($form['field_tijd']); ?>
    <?php print render($form['field_tijd_verzamelen']); ?>
     <?php print render($form['field_zichtbaar']); ?>

     <?php print render($form['field_verzend_e_mail']); ?>
  </div>
  <div class = 'right-collumn'>
     <?php print render($form['field_reageren']); ?>
     <?php print render($form['field_also_invite']); ?>
     <?php print render($form['field_invallers']); ?>
     <?php print render($form['field_gage']); ?>
  </div>
  <div class = 'clearfix'></div>
         <?php print drupal_render_children($form); ?>
</div>