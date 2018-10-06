function get_bit(val, i)
  if ((1 << (i - 1)) & val) > 0 then
    return 1;
  else
    return 0;
  end;
end

parity = 0
if myself == 13 then
  for i = 1, 12 do
    if get_bit(colors[i], i) == 1 then
      parity = 1 - parity
    end
  end
else
  for i = 1, 13 do
    if i ~= myself and get_bit(colors[i], myself) == 1 then
      parity = 1 - parity
    end
  end
end

hands = raise(parity == 1)

answer = 0
for i = 1, 12 do
  if i ~= myself then
    bit = 0
    for j = 1, 13 do
      if j ~= i and j ~= myself and get_bit(colors[j], i) == 1 then
        bit = 1 - bit
      end
    end
    if hands[i] ~= (bit == 1) then
      answer = answer + (1 << (i - 1))
    end
  end
end

if myself < 13 then
  bit = 0
  for i = 1, 12 do
    if i ~= myself and get_bit(colors[i], i) == 1 then
       bit = 1 - bit
    end
  end
  if hands[13] ~= (bit == 1) then
    answer = answer + (1 << (myself - 1))
  end
end
