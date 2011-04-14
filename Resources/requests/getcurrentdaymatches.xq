declare variable $document external;
element matches{
  let $matchlist := doc($document)//*:div//*:a[starts-with(@name, "today")]
  for $match in $matchlist
    return 
      element match{
	attribute teams { data($match/../../..//*:div[starts-with(@class, "team")])},
        attribute score {data($match/../../..//*:div[starts-with(@class, "chet")])},
        attribute begin {$match/../../..//*:div[starts-with(@class, "begin_txt")]/text() }
    }
}
