with Ada.Text_IO; use Ada.Text_IO;
with Ada.Long_Float_Text_IO; use Ada.Long_Float_Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Directories; use Ada.Directories;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with Ada.IO_Exceptions; use Ada.IO_Exceptions;
with Ada.Numerics; use Ada.Numerics;
with Ada.Numerics.Generic_Elementary_Functions;

procedure eCalc is
  filename : unbounded_string;
  Type Decimal is delta 0.00000001 digits 18;

  function getFilename return unbounded_string is
    filename: unbounded_string;
  begin
    put_line("Welcome to Euler e Estimation");
    put_line("Please enter a file for output: ");
    get_line(filename);
    -- check for existance of file
    if not Exists (To_String(filename)) then
      put("File doesn't exist, or cannot be found. ");
      filename := getFilename;
    end if;
    return filename;
    -- catch a NAME_ERROR exception
    exception
      when Ada.IO_Exceptions.NAME_ERROR =>
        put("Blank filenames are not allowed, ");
        return getFilename;
  end getFilename;

  procedure eCalculation(n: integer; filename: unbounded_string) is
    package Float_Functions is new Ada.Numerics.Generic_Elementary_Functions (Float);
    m: integer;
    test: Decimal;
    carry: integer;
    type intArray is array(Integer range <>) of Integer;
    temp: integer;
    outfp: file_type;
  begin
    Create (outfp,out_file,To_String (filename));
    put(outfp, "2.");

    m := 5;
    test := (n + 1) * 2.30258509;
    loop
      exit when Decimal(Float(m) * (Float_Functions.Log(Float(m)) - 1.0) + 0.5 * Float_Functions.Log(6.2831852 * Float(m))) > test;
      m := m+1;
    end loop;

    declare
      coef : intArray(0..m+1);
    begin
      for j in 2 .. m+1 loop
        coef(j) := 1;
      end loop;

      for i in 1 .. m+1 loop
        carry := 0;
        for j in reverse 1 .. m loop
          temp := coef(j) * 10 + carry;
          carry := temp/j;
          coef(j) := temp - carry * j;
        end loop;
        put(outfp,carry,width=>0);
      end loop;
    end;

    close(outfp);
  end eCalculation;

begin
  filename := getFilename;
  eCalculation(100,filename);

end eCalc;
