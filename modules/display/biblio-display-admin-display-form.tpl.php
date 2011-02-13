<table id="blocks" class="sticky-enabled">
	<thead>
    	<tr>
     		<th><?php print t('Field label'); ?></th>
      		<th><?php print t('Field name'); ?></th>
			<th><?php print t('Field Region'); ?></th>
    	</tr>
  	</thead>
	<tbody>
	<?php foreach ($field_listing as $i => $data): ?>
		<tr>
			<td><?php print $field_listing[ $i ]->label; ?></td>
			<td><?php print $field_listing[ $i ]->name; ?></td>
			<td><?php print $field_listing[ $i ]->region; ?></td>
		</tr>
	<?php endforeach; ?>
	</tbody>
</table>

<?php print $form_submit; ?>
