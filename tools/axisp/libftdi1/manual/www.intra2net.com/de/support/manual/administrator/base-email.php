<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>E-Mail | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base.php" title="Teil&nbsp;2.&nbsp;Allgemeine Funktionen"><link rel="prev" href="base-user-manager-importexport.php" title="14.3. Import/Export von Benutzerprofilen"><link rel="next" href="base-email-receive-client.php" title="15.2. E-Mail-Empfang auf dem Client (POP oder IMAP)">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="base-email.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-email.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">15. Kapitel - E-Mail</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-user-manager-importexport.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">Teil&nbsp;2.&nbsp;Allgemeine Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-email-receive-client.php">Weiter</a></td></tr></table><hr></div><div class="chapter" lang="de"><div class="titlepage"><div><div><h2 class="title"><a name="base-email"></a>15. Kapitel - E-Mail</h2></div></div></div><div class="toc"><p><b>Inhaltsverzeichnis</b></p><dl><dt><span class="sect1"><a href="base-email.php#base-email-send">15.1. E-Mail-Versand</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email.php#base-email-send-rights">15.1.1. Rechte</a></span></dt><dt><span class="sect2"><a href="base-email.php#base-email-send-submission">15.1.2. SMTP-Submission</a></span></dt><dt><span class="sect2"><a href="base-email.php#base-email-send-methods">15.1.3. Versandmethoden</a></span></dt><dt><span class="sect2"><a href="base-email.php#base-email-send-relay">15.1.4. Versand &uuml;ber Relayserver</a></span></dt><dt><span class="sect2"><a href="base-email.php#base-email-send-direct">15.1.5. Direkter Versand</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-receive-client.php">15.2. E-Mail-Empfang auf dem Client (POP oder IMAP)</a></span></dt><dt><span class="sect1"><a href="base-email-receive.php">15.3. E-Mail-Empfang auf dem Intranator</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-receive.php#base-email-receive-concepts">15.3.1. Konzepte</a></span></dt><dt><span class="sect2"><a href="base-email-receive.php#base-email-receive-pop">15.3.2. Abruf einzelner POP-Konten</a></span></dt><dt><span class="sect2"><a href="base-email-receive.php#base-email-receive-smtp">15.3.3. Direkte Zustellung per SMTP</a></span></dt><dt><span class="sect2"><a href="base-email-receive.php#base-email-receive-multidrop">15.3.4. Abruf von POP-Sammelkonten (Multidrop)</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-redirect.php">15.4. Weiterleitung von gesamten Domains</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-redirect.php#base-email-redirect-concept">15.4.1. Konzept</a></span></dt><dt><span class="sect2"><a href="base-email-redirect.php#base-email-redirect-adresschecking">15.4.2. Empf&auml;ngeradresspr&uuml;fung</a></span></dt><dt><span class="sect2"><a href="base-email-redirect.php#base-email-redirect-pop">15.4.3. Weiterleitung einzelner POP-Konten</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-addressing.php">15.5. E-Mail-Adressierung</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-addressing.php#d0e4032">15.5.1. Adresseinstellungen</a></span></dt><dt><span class="sect2"><a href="base-email-addressing.php#d0e4049">15.5.2. E-Mail-Adressen und Aliases</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-process.php">15.6. E-Mail-Verarbeitung</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-process.php#base-email-process-redirect">15.6.1. Weiterleitung</a></span></dt><dt><span class="sect2"><a href="base-email-process.php#base-email-process-answer">15.6.2. Automatische Antwort</a></span></dt><dt><span class="sect2"><a href="base-email-process.php#base-email-process-sort">15.6.3. Sortierung</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-filter.php">15.7. E-Mail-Filter</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-filter.php#base-email-filter-spam">15.7.1. Spamfilter</a></span></dt><dt><span class="sect2"><a href="base-email-filter.php#base-email-filter-virus">15.7.2. Virenscanner</a></span></dt><dt><span class="sect2"><a href="base-email-filter.php#base-email-filter-attachment">15.7.3. Anhangfilter</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-archiving.php">15.8. Archivierung</a></span></dt><dd><dl><dt><span class="sect2"><a href="base-email-archiving.php#base-email-archiving-interface">15.8.1. Schnittstelle</a></span></dt><dt><span class="sect2"><a href="base-email-archiving.php#base-email-archiving-mailstore">15.8.2. Anbindung des MailStore Servers</a></span></dt></dl></dd><dt><span class="sect1"><a href="base-email-automatic.php">15.9. Automatischer Transfer</a></span></dt><dt><span class="sect1"><a href="base-email-list.php">15.10. Verteiler</a></span></dt><dt><span class="sect1"><a href="base-email-configuration.php">15.11. Weitere Einstellungen</a></span></dt><dt><span class="sect1"><a href="base-email-queue.php">15.12. Warteschlange</a></span></dt><dt><span class="sect1"><a href="base-email-design.php">15.13. Aufbau des Mailsystems</a></span></dt><dt><span class="sect1"><a href="base-email-licensing.php">15.14. Unterschiede zwischen den Lizenzen</a></span></dt></dl></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-email-send"></a>15.1. E-Mail-Versand</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-send-rights"></a>15.1.1. Rechte</h3></div></div></div><a class="indexterm" name="base-email-send-rights1"></a><p>Der Intranator enth&auml;lt einen SMTP Server f&uuml;r den E-Mail-Versand. Alle Netzwerkobjekte
        (u.a. Netze, Rechner, VPNs,...), bei denen das Recht &#8222;E-Mail Relaying erlaubt&#8220; gesetzt ist
        (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-intranet-rights.php">Abschnitt&nbsp;9.2, &#8222;Zugriffsrechte eines Netzwerkobjekts&#8220;</a>) und die
        Firewalleinstellungen Zugriff auf den SMTP-Port erlauben, d&uuml;rfen den Intranator zum Senden
        von E-Mails ins Internet (relayen) ohne weitere Authentifizierung verwenden.</p><p>Aus Netzen ohne das Recht &#8222;E-Mail Relaying erlaubt&#8220; (z.B. auch dem Internet) ist es nach
        Authentifizierung mit einem aktiven Account aus dem Benutzermanager (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-user-manager-user.php">Abschnitt&nbsp;14.2, &#8222;Benutzer&#8220;</a>) und entsprechenden
        Rechten (siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-user-manager.php#base-user-manager-groups-rights">Abschnitt&nbsp;14.1.1, &#8222;Zugriffsrechte&#8220;</a>) auch erlaubt.</p><p>Der Versand von E-Mails an lokale Adressen des Intranators ist kein Relaying und ist aus
        allen Netzen, denen die Firewall Zugriff auf den SMTP-Port gestattet, m&ouml;glich.</p><a class="indexterm" name="d0e3360"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-send-submission"></a>15.1.2. SMTP-Submission</h3></div></div></div><a class="indexterm" name="base-email-send-submission1"></a><p>Einige Internetprovider erlauben Ihren Kunden keinen direkten Verbindungsaufbau zu
        TCP-Port 25 (SMTP) um den Versand von Spam zu minimieren. Dadurch ist es dann aber auch
        nicht mehr m&ouml;glich, den Intranator zu nutzen, um von unterwegs aus E-Mails zu versenden.
        Daher unterst&uuml;tzt der Intranator SMTP-Submission auf TCP-Port 587.</p><p>Stellen Sie Ihren mobilen E-Mail-Client einfach von Port 25 auf Port 587 um und
        aktivieren die Authentifizierung mit Ihrem Intranator-Benutzernamen. Au&szlig;erdem sollten Sie
        die Verschl&uuml;sselung per TLS aktivieren (in manchen Programmen f&auml;lschlicherweise SSL
        genannt).</p><a class="indexterm" name="d0e3375"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-send-methods"></a>15.1.3. Versandmethoden</h3></div></div></div><p>E-Mails ins Internet k&ouml;nnen entweder direkt an den Zielserver oder an einen
        SMTP-Relayserver gesendet werden, der dann den weiteren Versand &uuml;bernimmt. Relayserver
        bieten eigentlich alle Provider von Webseiten, aber auch viele Zugangsprovider an.</p><p>Um das Spamaufkommen zu verringern, nehmen die meisten Mailserver keine direkt
        versendeten Mails mehr von IPs an, die f&uuml;r Einwahl oder DSL genutzt werden. Wir raten daher
        unbedingt zur Verwendung eines Relayservers.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Die Versand- und Empfangswege von E-Mails sind unabh&auml;ngig voneinander. Sie k&ouml;nnen also
          problemlos z.B. E-Mails direkt per SMTP empfangen, f&uuml;r den Versand aber einen Relayserver
          verwenden.</p></td></tr></table></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-send-relay"></a>15.1.4. Versand &uuml;ber Relayserver</h3></div></div></div><a class="indexterm" name="base-email-send-relay1"></a><a class="indexterm" name="base-email-send-relay2"></a><p>E-Mail-Relayserver werden als Versandprofil unter
        Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Versand hinterlegt. Um unterschiedliche
        E-Mail-Versandmethoden f&uuml;r unterschiedliche Internet-Provider zu erm&ouml;glichen, werden diese
        Versandprofile unter
        Netzwerk&nbsp;&gt;&nbsp;Provider&nbsp;&gt;&nbsp;Profile&nbsp;:&nbsp;Dienste den
        verschiedenen Internetprovidern zugewiesen und aktiviert, sobald der Intranator mit dem
        entsprechenden Provider online ist.</p><p>Beinahe alle Relayserver fordern eine Authentifizierung mit Login und Passwort &uuml;ber
        SMTP-AUTH. Das alte Verfahren SMTP-after-POP kommt heutzutage kaum noch zum Einsatz und
        sollte auf SMTP-AUTH umgestellt werden.</p><a class="indexterm" name="d0e3407"></a><a class="indexterm" name="d0e3408"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-send-direct"></a>15.1.5. Direkter Versand</h3></div></div></div><a class="indexterm" name="base-email-send-direct1"></a><a class="indexterm" name="base-email-send-direct2"></a><p>Viele E-Mail-Provider verwenden relativ aggressive Methoden, um dem Empfang von Spam zu
        reduzieren. Daher wird die Konfiguration und Anbindung der sendenden E-Mail-Server Tests
        unterworfen, bevor E-Mails durchgelassen werden. Es empfiehlt sich daher in den meisten
        F&auml;llen, den Versand &uuml;ber einen Relayserver abzuwickeln (siehe voriges Kapitel).</p><p>Wer E-Mails direkt versenden will, muss vorher folgende Kriterien erf&uuml;llen: </p><div class="itemizedlist"><ul type="disc"><li><p>Vom Provider fest zugewiesene IP-Adresse.</p></li><li><p>Die DNS-R&uuml;ckw&auml;rtsaufl&ouml;sung (reverse lookup, PTR-Eintrag) f&uuml;r die IP muss m&ouml;glich
              sein und exakt mit dem externen E-Mail-Servernamen des Intranators &uuml;bereinstimmen.
              Dieser wird unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Einstellungen
              festgelegt. Wollen Sie die R&uuml;ckw&auml;rtsaufl&ouml;sung eintragen oder &auml;ndern, wenden Sie sich
              an Ihren Zugangsprovider; er muss diese Einstellung f&uuml;r Sie vornehmen. Unter
              System&nbsp;&gt;&nbsp;Diagnose&nbsp;&gt;&nbsp;DNS k&ouml;nnen Sie Ihre externe IP eingeben
              und &uuml;berpr&uuml;fen, wie die DNS-R&uuml;ckw&auml;rtsaufl&ouml;sung Ihrer IP eingestellt ist.</p></li><li><p>
              <a class="indexterm" name="base-email-send-direct3"></a> Der unter Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Einstellungen
              eingestellte externe E-Mail-Servername muss per DNS abfragbar sein (Vorw&auml;rtsaufl&ouml;sung,
              A-Eintrag) und auf die externe IP des Intranators zeigen. Um diesen DNS-Eintrag
              anzulegen, wenden Sie sich an Ihren Webspace- oder Domain-Provider.</p><a class="indexterm" name="d0e3446"></a></li><li><p>Die fest zugewiesene IP-Adresse sollte auf den Kunden selbst und nicht den
              Provider registriert sein. Dies kann beim RIPE unter <a class="ulink" href="http://www.ripe.net/" target="_top">http://www.ripe.net/</a> &uuml;berpr&uuml;ft werden.</p></li></ul></div><p>
      </p><a class="indexterm" name="d0e3453"></a><a class="indexterm" name="d0e3454"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-user-manager-importexport.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-email-receive-client.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">14.3. Import/Export von Benutzerprofilen&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;15.2. E-Mail-Empfang auf dem Client (POP oder IMAP)</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>