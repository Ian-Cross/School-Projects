class Token {

  public final static int ERROR = 0;
  public final static int NOTHING = 1;
  public final static int OPENTAG = 2;
  public final static int CLOSETAG = 3;
  public final static int WORD = 4;
  public final static int NUMBER = 5;
  public final static int PUNCTUATION = 6;
  public final static int HYPHENATED = 7;
  public final static int APOSTROPHIZED = 8;

  public int m_type;
  public String m_value;
  public int m_line;
  public int m_column;

  Token (int type, String value, int line, int column) {
    m_type = type;
    m_value = value;
    m_line = line;
    m_column = column;
  }

  public String toString() {
    switch (m_type) {
      case OPENTAG:
        return "OPEN-" + m_value + "\n";
      case CLOSETAG:
        return "CLOSE-" + m_value + "\n";
      case WORD:
        return "WORD(" + m_value + ")\n";
      case NUMBER:
        return "NUMBER(" + m_value + ")\n";
      case PUNCTUATION:
        return "PUNCTUATION(" + m_value + ")\n";
      case HYPHENATED:
        return "HYPHENATED(" + m_value + ")\n";
      case APOSTROPHIZED:
        return "APOSTROPHIZED(" + m_value + ")\n";
      case NOTHING:
        return "";
      default:
        return "UNKNOWN(" + m_value + ")\n";
    }
  }
}
