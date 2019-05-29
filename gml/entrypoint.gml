#define zgm8c_init

var is_gm81141;
is_gm81141 = false;

if (gamemaker_version == 810)
if (string_char_at('!', 0) == '')
if (execute_string('return get_function_address( "clamp" );') > 0)
if (execute_string('return get_function_address( "lerp" );') > 0)
  is_gm81141 = true;

if !is_gm81141 {
  zgm8c_abort81141(window_handle());
  exit;
}

surface_free(surface_create(0, 0));


#define ansi

var s, r;
s = zgm8c_ansi(argument0);
r = s*ansi_char(0);
zgm8c_buffer(s, r);
return r;


#define utf8

var s, r;
s = zgm8c_utf8(argument0);
r = s*ansi_char(0);
zgm8c_buffer(s, r);
return r;


#define string_utf8_insert

var s, r;
s = zgm8c_string_insert(argument0, argument1, argument2);
r = s*ansi_char(0);
zgm8c_buffer(s, r);
return r;

//