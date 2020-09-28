
ABOUT BULK CREATOR
------------------
It happens to create complex content types with tens, sometimes hundreds fields.
Or to edit such content types to add more fields. Think e.g., what it takes
to compile a balance sheet, i.e., a load of integer fields which names are
handily retrievable by a CSV document.

In Drupal, fields must be added one by one with the usual delay of the physical
db creation and the manual setting of each field.

This module helps to automate this process providing helpers, functions and 
an administration GUI to generate / bulk create new content types and fields
in two shakes of a lamb's tail. Or, through helper functions, to
programmatically add field to content types and/or content types.

Further functions:
- Exploiting drush, you will be able to call functions also from console.
- You can create a number of fields by jolly patterns, e.g., field_[a1--b9]
- You can create your personalized callback function (example in the code)
- You can add your field to an existing or bulk created field group!


USAGE
-----
After installed and enabled the module, go to the configuration page.
Follow the instructions to launch a script.

1) Write or paste the bulk script (see the next section).
2) Select the other parameters, e.g., the field separator.
3) Write the name of your custom callback function if you need to call it.

You can also:
- Use the module also from the console through drush. See Usage Examples.
- Use your callback function to personalize the parsing behavior.


THE BULK SCRIPT
---------------
A bulk script is a text content which every line is a command:
[<line_command>]
[<line_command>]
[...]

Empty lines, or lines starting with the '#' character are not computed.

A line command contains its parameters:
<line_command> := <content_type>; <field_type>; <field_machine_name>; 
    [<field_label>]; [<field_required>]; [<field_description>];
    [<field_default>]; [<field_group>];
    [<field_prefix>]; [<field_suffix>];

And the parameters are:
<content_type> := The content type bundle the field instance will
    be attached to. This content type will be created if missing.
<field_type> := The field type. Use the Drupal Fields Type name [dr_01],
    see, e.g., [dr_02] for an integer field settings.
<field_machine_name> := The Machine name of the field. Note: You can put here
    the field label: it will be translated to a Drupal machine name.
    You can use jolly patterns to create multiple fields such as field_[a9--b2].
[<field_label>] := The field label. If missing it will be guessed from
    the machine name.
[<field_description>] := The field description. Default, empty.
[<field_required>] := TRUE or FALSE if the field is required. Default, FALSE.
[<field_default>] := The default value of the field.
[<field_group>] := The name of the field group the new field to be a child.
[<field_prefix>] := The field prefix (e.g., '€'). Default empty.
[<field_suffix>] := The field suffix (e.g., 'meters'). Default empty.
    (More parameters will be added in the future)

Jolly characters are allowed inside machine names. E.g. field_[a9--b2] will
create field_a9, field_b0, field_b1, field_b2. Can you feel the power of it?
Labels will be automatically completed according to the string token.


USAGE EXAMPLES
--------------
Note that you can call these functions from the console drush shell, e.g., 
> drush php-eval "bulk_field_create('new_type', 'number_integer',
    'balance_accounts_payable');
The module is developed to give you a feedback also when working on console.

- Create a new content type.
bulk_ct_create('new_type', 'My New Content Type', 'A test Content Type');

- Delete a content type
bulk_ct_delete('new_type');"

- Create a new integer field for the content type 'new_type'
bulk_field_create('new_type', 'number_integer', 'balance_accounts_payable',
  'Accounts Payable', 'New Voice for Balance Sheet', FALSE, '0', '', '€');
bulk_field_create('new_type', 'number_integer', 'Balance - Accounts Payable');

- Launch a script from file.
bulk_field_create_from_file('/home/artsakenos/balance-sheet.bulk');

- Custom function example
  (you can find this example of a personalized callback in the code).
bulk_custom_field_add_balance('B.123 My Voice of Balance');

- Bulk Script Example
# Add a new_type content, because it does not exists, and a field on it:
new_type; number_integer; field_price_01; My new Price Field; This is the price
  of the item; FALSE; 0; group_new; €
# Add the fields field_text_b8, ...b9, ...c0, ...c1, field_text_c2 to article
article; text; field_text_[b8--c2]; My New Text Field in Article; 
# Add a new text field in new_type, take care of all the labels.
new_type; text; new_text_field;


FUTURE WORK
-----------
Your suggestions and patches are welcome for further improvements.

Next steps:
- Add a more complete reference to the field instance settings
- Allow custom line and field separator, and line comment
- Change button name, 
    $form['actions']['submit']['#value'] = t('Launch Bulk Script');
    does not work.
- Add translations (You can send yours if interested).

REFERENCES
----------
[dr_01] https://www.drupal.org/node/1879542
[dr_02] https://api.drupal.org/api/drupal/modules%21field%21modules%21number%21number.module/function/number_field_info/7
