
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
		<div class="contentleft">
    <?php
			print render($left);
    ?>
		</div>
		<div class="contentright">
			<?php
				print render($right);
			?>
		</div>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</div>
