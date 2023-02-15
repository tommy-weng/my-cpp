void LoadInterpreter::printAvgLoadBuffer(u32 cellId, DataType dataType)
{
  formatTime();
  std::cout << "cellId=" << cellId << ",dataType=" << dataType << ",avgLoadBuffer=[" << std::endl;
  of << "cellId="<< cellId << ",dataType=" << dataType << ",avgLoadBuffer=[" << std::endl;
  for (u32 i = 0; i < NUM_OF_INPUT; i++)
  {
    if (0 == i % 10)
    {
      std::cout << "  ";
      of << "  ";
    }

    const float* inputLoadBuffer = getLoadBuffer(cellId, dataType);
    std::cout.setf(std::ios::left);
    of.setf(std::ios::left);
    std::cout.width(10);
    of.width(10);
    std::cout << inputLoadBuffer[i];
    of << inputLoadBuffer[i];
    if ((NUM_OF_INPUT - 1) == i)
    {
      std::cout << "]";
      of << "]";
    }
    else
    {
      std::cout << ", ";
      of << ", ";
    }

    if ((0 == (i + 1) % 10)  || ((NUM_OF_INPUT - 1) == i))
    {
      std::cout << std::endl;
      of << std::endl;
    }
  }
}