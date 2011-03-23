<?php if (!count($elements['items'])): ?>
    <div id="noitems"><b><?php print t('There is no items for this record'); ?></b></div>
<?php else: ?>
    <span><b><?php print $elements['avail'] . ' / ' . $elements['total'] . t(' item(s) are available(s)');  ?></b></span>
    <div id="items">
    <table>
	<tr>
	    <th><?php print t('Call Number'); ?></th>
	    <th><?php print t('Branch'); ?></th>
	    <th><?php print t('Location'); ?></th>
	    <th><?php print t('Status'); ?></th>
	</tr>
	<?php foreach ($elements['items'] as $itemnumber => $item) : ?>
	    <tr>
		<td><?php print $item['callnum']; ?></td>
		<td><?php print $item['branch']; ?></td>
		<td><?php print $item['location']; ?></td>
		<td><?php print $item['avail'] == 1 ? t('Available') : t('Unavailable'); ?></td>
	    </tr>
	<?php endforeach; ?>
    </table>
    </div>
<?php endif; ?>
