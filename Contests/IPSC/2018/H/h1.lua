parity = 0
for i = 1, N do
    if i ~= myself and colors[i] == 1 then
       parity = 1 - parity
    end
end

my_bool = (parity == 1)
hands = raise(my_bool)

helper = myself + 1
if myself == 13 then
   helper = myself - 1
end

if colors[helper] == 1 then
   parity = 1 - parity
end

if hands[helper] == (parity == 1) then
   answer = 2
else
   answer = 1
end
