import Math.NumberTheory.Primes

bigInt = 5000

p :: Integer
p = (unPrime . nextPrime) bigInt

q :: Integer
q = (unPrime . precPrime) bigInt

n :: Integer
n = p * q

phi_ :: Integer -> Integer -> Integer
phi_ p q = (p - 1) * (q - 1)

phi = phi_ p q

nwd_ :: Integer -> Integer -> Integer
nwd_ a 0 = a
nwd_ a b = nwd_ b (a `mod` b)

e_ :: Integer -> Integer
e_ phi = until (\x -> nwd_ x phi == 1) (+ 1) 10

e = e_ phi

primesToPhi :: Integer -> [Prime Integer]
primesToPhi n = [(nextPrime 1) .. precPrime n]

d_ :: Integer -> Integer -> [Prime Integer] -> Integer
d_ e phi (p : ps) =
  let prime = unPrime p
   in if (e * prime) `mod` phi == 1
        then prime
        else d_ e phi ps

d = d_ e phi (primesToPhi phi)

data PublicKey where
  PublicKey :: Integer -> Integer -> PublicKey

data PrivateKey where
  PrivateKey :: Integer -> Integer -> PrivateKey

encrypt :: PublicKey -> Char -> Integer
encrypt (PublicKey e n) m = fromIntegral (fromEnum m) ^ e `mod` n

decrypt :: PrivateKey -> Integer -> Char 
decrypt (PrivateKey d n) c = toEnum (fromInteger (c ^ d `mod` n))

encryptMessage :: PublicKey -> String -> [Integer]
encryptMessage keys = map (encrypt keys)

decryptMessage :: PrivateKey -> [Integer] -> String
decryptMessage keys = map (decrypt keys)

publicKey = PublicKey e n
privateKey = PrivateKey d n

main = do
  message <- getLine
  let encryptedMessage = encryptMessage publicKey message
  let decryptedMessage = decryptMessage privateKey encryptedMessage
  print encryptedMessage 
  print decryptedMessage
