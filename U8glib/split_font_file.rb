if File.exists? 'utility/u8g_font_data.c'
    File.rename 'utility/u8g_font_data.c', 'utility/u8g_font_data.c.bak'
end

if  not File.exists? 'utility/u8g_font_data.c.bak'
    puts 'Unable to find font data file utility/u8g_font_data.c.bak'
    exit
end

code = File.read('utility/u8g_font_data.c.bak').encode("utf-8")
code.scan(/\/*.+?\};/m) do |font_def|
    font_name = font_def.match(/const u8g_fntpgm_uint8_t u8g_font_(.+?)\[/)[1]
    file_name = "utility/u8g_font_data_#{font_name}.c"
    File.open(file_name, 'w'){|file| file.write font_def}
end
