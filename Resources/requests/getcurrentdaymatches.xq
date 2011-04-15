declare variable $document external;
element matches{
  let $matchlist := doc($document)//*:div//*:a[starts-with(@name, "today")]
  for $match in $matchlist
    let $team1 := $match/../../..//*:div[starts-with(@class, "team")]//*:a[1]/text()
    let $team2 := $match/../../..//*:div[starts-with(@class, "team")]//*:a[2]/text()
    let $chet := data($match/../../..//*:div[starts-with(@class, "chet")])
    let $chetmore := $match/../../..//*:table[starts-with(@class, "chet_more")]//*:tr//*:td/text()
    let $begin := $match/../../..//*:div[starts-with(@class, "begin_txt")]/text()
    return 
      element match{
	attribute teams {concat(concat($team1, "-"), $team2)},
        attribute score {$chet},
        attribute begin {$begin},
        attribute comment {$chetmore}
    }
}
