with Ada.Text_IO; use Ada.Text_IO;
with Ada.Directories; use Ada.Directories;
with ada.strings.unbounded; use ada.strings.unbounded;
with ada.strings.unbounded.Text_IO; use ada.strings.unbounded.Text_IO;
with Ada.IO_Exceptions; use Ada.IO_Exceptions;
with Ada.Numerics.Float_Random; use Ada.Numerics.Float_Random;
with Ada.Numerics.Discrete_Random;

procedure wordscram is
  filename : unbounded_string;

  -------------------
  -- Desc: Prompt and retrieve a filename from the user
  -- Returns: unbounded_string: inputted filename
  -------------------
  function getFilename return unbounded_string is
    filename: unbounded_string;
  begin
    -- Prompt and take in users file
    put_line("Please enter a file name");
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

  -------------------
  -- Desc: Determins if character c is a word breaking character
  -- Params: character: the character to be checked
  -- Returns: boolean: false if c is not word breaking, true if word breaking
  -------------------
  function isDelim (c: character) return boolean is
  begin
    -- check the characters ascii value
    case Character'Pos (c) is
      when 0..47 | 58..64 | 123..127 =>
        return TRUE;
      when others =>
        return FALSE;
    end case;
  end isDelim;

  -------------------
  -- Desc: Determins if character c is alphebetical
  -- Params: character: the character to be checked
  -- Returns: boolean: false if is not alphebetical, true if alphebetical
  -------------------
  function isAlpha (c: character) return boolean is
  begin
    -- check the characters ascii value
    case Character'Pos (c) is
      when 97..122 | 65..90 =>
        return TRUE;
      when others =>
        return FALSE;
    end case;
  end isAlpha;

  -------------------
  -- Desc: Checks every character in the string (s) to determin if it is a useable word
  -- Params: unbounded_string: a string of characters representing a word
  -- Returns: boolean: false if any character is not alphebetical, true otherwise
  -------------------
  function isWord (s: unbounded_string) return boolean is
    c: character;
  begin
    for i in 1 .. Length(s) loop
      c := Element(s, i);
      if not isAlpha(c) then
        return FALSE;
      end if;
    end loop;
    return TRUE;
  end isWord;

  -------------------
  -- Desc: Takes the inputted string, saves the first and last character scrambling the internal letters
  -- Params: unbounded_string: a string of characters representing a word
  --         integer: the length of the unbounded_string,
  -- Returns:
  -------------------
  procedure scrambleWord(word: unbounded_string; length: integer) is
    Gen: Ada.Numerics.Float_Random.Generator;
    type Int_Arr is array (0..length) of Integer;

    -------------------
    -- Desc: Uses Numerics.Float_Random to generate a random number between a, and b
    -- Params: integer: the lower bound of the random range,
    --         integer: the upper bound of the random range
    -- Returns: integer: a random integer between a and b
    -------------------
    function randomInt(a: integer; b: integer) return Integer is
    begin
      return a + Natural(Ada.Numerics.Float_Random.Random(Gen) * Float(b));
    end randomInt;

    indices: Int_Arr;
    index: integer;
    letter: character;
    wordString: string(1..length);
  begin
    -- convert the unbounded_string to a bounded one
    wordString := To_string(word);
    -- conditional scrambling
    if length > 0 then
      if length <= 3 then
        put(word);
      else
        -- send the first character out
        put(wordString(1..1));

        -- seed the generator, and loop through the internal letters
        Ada.Numerics.Float_Random.Reset(Gen);
        for i in 1..length-2 loop
          -- pick a random number of the number of letters left
          index := randomInt(2,length-2-i);
          letter := wordString(index);
          put(letter);
          -- move that letter to the back of the word
          wordString(index..length-2) := wordString(index+1..length-1);
          wordString(length-1) := letter;
        end loop;

        -- send the last character out
        put(wordString(length..length));
      end if;
    end if;
  end scrambleWord;

  -------------------
  -- Desc: Prompt and retrieve a filename from the user
  -- Returns: unbounded_string: inputted filename
  -------------------
  procedure processText(filename: unbounded_string) is
    -- words: sentence;
    line: unbounded_string;
    word: unbounded_string;
    buffer: unbounded_string;
    infp: file_type;
    c: character;
  begin
    open(infp,in_file,To_String (filename));
    loop
      exit when end_of_file(infp);
      get_line(infp,line);

      for i in 1 .. Length(line) loop
        c := Element(line, i);
        -- checking for word breaks
        if isDelim(c) then
          scrambleWord(buffer, length(buffer));
          put(c);
          buffer := Delete(buffer,1,Length(buffer));
        else
          Append(buffer,c);
        end if;
      end loop;

      -- catch the ending word
      scrambleWord(buffer, length(buffer));
      -- clear the buffer
      buffer := Delete(buffer,1,Length(buffer));
      new_line;

    end loop;
    close(infp);
  end processText;

begin
  filename := getFilename;
  processText(filename);

end wordscram;
