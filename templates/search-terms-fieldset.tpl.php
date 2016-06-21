<div id="ting-search-terms-container"></div>
<div class="search-term-op-bar">
  <?php if (!empty($ops)): ?>
    <div class="search-term-ops">
      <?php foreach ($ops as $op): ?>
        <div class="search-term-op">
          <?php print $op; ?>
        </div>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>
  <?php if (!empty($more_link)): ?>
    <div class="search-terms-more">
      <?php print $more_link; ?>
    </div>
  <?php endif; ?>
</div>
