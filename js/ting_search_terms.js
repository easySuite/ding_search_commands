(function ($) {
  'use strict';

  /**
   * Get last search term from the input value.
   */
  function getLastTerm(value) {
    var result = '';
    if (value !== '') {
      result =  value.split(/\s/).pop();
    }

    return result;
  }

  Drupal.behaviors.selectSearchTerms = {
    attach: function(context, settings) {
      var $searchField = $('input[name=search_block_form]');

      // Append logical operation to the search field input.
      $('.search-term-op').on('click', function (event) {
        if ($searchField.val() != '') {
          $searchField.val($searchField.val() + ' ' + $(this).text() + ' ');
        }
        $searchField.focus();
      });

      // Move focus on textfield on fieldset link click.
      $('.fieldset-title').click(function () {
        if (!$searchField.hasClass('collapsed')) {
          $searchField.focus();
        }
      });

      // Provide autocomplete methods.
      $.widget('ting.searchTerms', $.ui.autocomplete, {
        // Render each item list and append it to autocomplete list.
        _renderItem: function (ul, item) {
          return $("<li class='search-term'/>")
            .append('<p class="search-key">' + item.value + '</p><p class="search-description">' + item.description + '</p>')
            .appendTo(ul);
        }
      });

      // Get all terms.
      var searchTerms = Drupal.settings.searchTerms;

      // Initiate terms autocomplete.
      $searchField.searchTerms({
        minLength: 0,
        // source: searchTerms,
        source: function (request, response) {
          console.log(getLastTerm(request.term));
          // TODO: replace last inserted term with the suggested one.
          // It seems that it is necessary to be inserted in the select function.
          response($.ui.autocomplete.filter(searchTerms, getLastTerm(request.term)));
        },
        appendTo:'#ting-search-terms-container',
        // Append term value to the textfield.
        select: function (event, ui) {
          $(this).val($(this).val() + ui.item.value + '=');
          $(this).focus();

          return false;
        },
/*        // Prevent value inserted on focus.
        focus: function(event, ui) {
          return false;
        },*/
        // Keep autocomplete open all the time.
        close: function (event, ui) {
          $(this).searchTerms("search", "");
        }
      })
      // Display all items on fieldset expand.
      .focus(function () {
        $(this).searchTerms("search", "");
      });
    }
  };
})(jQuery);
