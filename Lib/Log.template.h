
//Need Functions in headers so templates can be instantiated
//Still need to think of a neater solution
template <typename T> static void _handleCol(const std::string &col, std::ostream& out)
{
  //Already check for correct type in Logger::operator<<
  #ifdef COLOUR_TERMINAL
    static std::string lastCol = "";

    if(col != lastCol)
    {
      lastCol = col;
      out << lastCol;
    }
  #endif //COLOUR_TERMINAL
}

template <class T> Logger& operator<< (Logger& log, const T& val)
{
  if(log.getLogging())
  {
    _handleCol<T>(log.getColour(), log.getStream());
    log.getStream() << val;
  }

  return log;
}
