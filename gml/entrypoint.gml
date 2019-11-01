#define zgm8c_init

var is_81141, is_8121x;
is_81141 = false;
is_8121x = false;

if (gamemaker_version == 810) if (string_char_at('!', 0) == '')
if (execute_string('return get_function_address("clamp")') > 0)
if (execute_string('return get_function_address("lerp")') > 0) {
  is_81141 = execute_string('return get_function_address("display_get_orientation")') <= 0;
  is_8121x = execute_string('return get_function_address("dot_product_normalised")') > 0;
}

if !is_81141 && !is_8121x {
  zgm8c_abort_startup();
  exit;
}

surface_free(surface_create(0, 0));


#define ansi

var b;
b = zgm8c_ansi(argument0)*"?";
zgm8c_result(b);
return b;


#define utf8

var b;
b = zgm8c_utf8(argument0)*"?";
zgm8c_result(b);
return b;


#define string_utf8_insert

var b;
b = zgm8c_string_insert(argument0, argument1, argument2)*"?";
zgm8c_result(b);
return b;

//