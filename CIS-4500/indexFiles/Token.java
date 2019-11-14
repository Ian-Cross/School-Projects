class Token {

  public final static int ERROR = 0;
  public final static int LAB = 1;
  public final static int PUNC = 2;
  public final static int NEW = 3;
  public final static int APOS = 4;
  public final static int HYPH = 5;
  public final static int WORD = 20;
  public final static int NUM = 21;

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
      case WORD:
      case NUM:
      case LAB:
      case PUNC:
      case APOS:
      case HYPH:
      case NEW:
        return m_value;
      case ERROR:
        return "Err(" + m_value + ") ";
      default:
        return "Def(" + m_value + ") ";
    }
  }
}
